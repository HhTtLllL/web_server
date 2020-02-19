//##################################################################
// File Name: http_conn.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年02月18日 星期二 16时11分42秒
//=============================================================
//!/usr/bin/python

#include "http_conn.h"


//定义HTTP相应的一些状态信息
const char* ok_200_title = "OK";
const char* error_400_title = "Bad Request";
const char* error_400_form = "Your request has bad syntax or is inherently impossible to satisfy.\n";
const char* error_403_title = "Forbidden";
const char* error_403_form = "you do not have permission to get file from this server.\n";
const char* error_404_title = "Not Found";
const char* error_404_form = "The requested file was not found on this server.\n";
const char* error_500_title = "Internal Error";
const char* error_500_form = "there was an unusual problem serving the requested file.\n";

//网站的根目录

const char* doc_root = "./dir";

//设置套接字为非阻塞
int setnonblocking(int fd)
{
	int old_option = fcntl(fd,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option;
}

void addfd(int epollfd,int fd,bool one_shot)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
				//EPOLLET  将epoll设置为边缘触发,假设对事件没做处理，内核不会反复通知事件就绪
				//EPOLLRDHUP 对端断开连接, 
	if(one_shot)
	{
		event.events |= EPOLLONESHOT; //只监听一次事件
	}

	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnonblocking(fd);
}



//在epoll树上删除结点
void removefd(int epollfd,int fd)
{
	epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,0);
	close(fd);   
}

//修改监听事件
void modfd(int epollfd,int fd,int ev)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
	epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event);
}

int http_conn::m_user_count = 0;
int http_conn::m_epollfd = -1;


//关闭连接
void http_conn::close_conn(bool real_close)
{
	if(real_close && (m_sockfd != -1))
	{
		removefd(m_epollfd,m_sockfd);
		m_sockfd = -1;
		m_user_count--;   //关闭连接时,将总客户量减一
	}
}

//初始化一个连接
void http_conn::init(int sockfd,const sockaddr_in& addr)
{
	m_sockfd = sockfd;
	m_address = addr;
	
	//下面两行为了避免TIME_WAIT状态,仅用于调试,实际使用时应该去掉
	int reuse = 1;
	//设置端口复用
	setsockopt(m_sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	
	addfd(m_epollfd,sockfd,true);
	m_user_count++;

	//初始化连接
	init();
}

//初始化连接
void http_conn::init()
{
	m_checked_state = CHECK_STATE_REQUESTLINE;
	m_linger = false;

	m_method = GET;
	m_url = 0;
	m_version = 0;
	m_content_length = 0;
	m_host = 0;
	m_start_line = 0;
	m_checked_idx = 0;
	m_read_idx = 0;
	m_write_idx = 0;
	memset(m_read_buf,'\0',READ_BUFFER_SIZE);
	memset(m_write_buf,'\0',WRITE_BUFFER_SIZE);
	memset(m_real_file,'\0',FILENAME_LEN);

}

//从状态机
http_conn::LINE_STATUS http_conn::parse_line()
{
	char temp;
	//m_checked_idx 指向buffer(应用程序的缓冲区)中当前正在分析的字节,
	//m_read_index  指向buffer中客户数据的尾部的下一字节.
	//buffer中第0 ~ m_check_idx字节都已经分析完毕
	//第m_checked_index ~ (m_read_index - 1 ) 字节在下面的循环分析
	printf("check_idx = %d,read_idx = %d\n",m_checked_idx,m_read_idx);
	for(;m_checked_idx < m_read_idx;++m_checked_idx)
	{
		//获取当前字节
		temp = m_read_buf[m_checked_idx];
		//如果当前字节为 '\r' ,即回车符,则说明可能读取到一个完整的行
		if(temp == '\r')
		{
			//如果'\r' 字符是目前buffer中最后一个已经被读入的客户数据,那么
			//这次分析没有读取到一个完整的行,返回LINE_OPEN ,用来表示还需要
			//继续读取客户数据才能进一步分析
			if((m_checked_idx + 1) == m_read_idx)
			{
				return LINE_OPEN;
			}
			//如果下一个字符为 '\n'   则说明读取到一个完整的行
			else if(m_read_buf[m_checked_idx + 1] == '\n')
			{
				//将 '\r','\n' 变为 '\0'
				m_read_buf[m_checked_idx++] = '\0';
				m_read_buf[m_checked_idx++] = '\0';
				
				return LINE_OK;
			}
			//否则的话,说明客户发送的HTTP请求存在语法错误
			return LINE_BAD;
		}
		//如果当前的字节是 '\n'  换行符,则也说明可能读取到一个完整的行
		else if(temp == '\0')
		{
			if(( m_checked_idx > 1) && (m_read_buf[m_checked_idx - 1] == '\r')) 
			{
				m_read_buf[m_checked_idx - 1] = '\0';
				m_read_buf[m_checked_idx++] = '\0';

				return LINE_OK;
			}

			return LINE_BAD;
		}

	}
	//如果所有内容都分析完毕也没有遇到 '\r' 字符,则返回LINE_OPEN 表示还需要继续读取客户
	//数据才能进一步分析
	return LINE_OPEN;
}

//循环读取客户数据,直到无数据可读或者对方关闭连接
bool http_conn::read()
{
	if(m_read_idx >= READ_BUFFER_SIZE)
	{
		return false;
	}

	int bytes_read = 0;
	while(true)
	{
		bytes_read = recv(m_sockfd,m_read_buf + m_read_idx,READ_BUFFER_SIZE - m_read_idx,0);
		if(bytes_read == -1)
		{
			if(errno == EAGAIN || errno == EWOULDBLOCK)
			{
				break;
			}

			return false;
		}
		else if(bytes_read == 0)
		{
			return false;
		}

		m_read_idx += bytes_read;
	}

	return true;
}

//解析HTTP请求行,获得请求方法,目标URL,以及HTTP版本号
http_conn::HTTP_CODE http_conn::parse_request_line(char* text)
{
	printf("text ==== %s\n",text);
	//																								空格,\t	
	//依次检测text 中的字符,当被检测的字符在字符串" \t" 中也包含时,则停止监测,返回该字符的位置
	m_url = strpbrk(text," \t");
	//如果请求行中没有空白字符或者'\t'  ,则HTTP请求一定有问题
	if(!m_url)
	{
		return BAD_REQUEST;
	}

	*m_url++ = '\0';

	char* method = text;
	if(strcasecmp(method,"GET") == 0) //仅支持GET
	{
		m_method = GET;
	}
	else
	{
		return BAD_REQUEST;
	}

	//检测 m_url 中第一个不在字符串 " \t"  中出现的字符的下标
	m_url += strspn(m_url," \t");
	m_version = strpbrk(m_url," \t");

	if(!m_version)
	{
		return BAD_REQUEST;
	}
	
	*m_version++ = '\0';
	m_version += strspn(m_version," \t");
	if(strcasecmp(m_version,"HTTP/1.1") != 0)
	{
		return BAD_REQUEST;
	}

	if(strncasecmp(m_url,"http://",7) == 0)
	{
		m_url += 7;
		m_url = strchr(m_url,'/');
	}

	if(!m_url || m_url[0] != '/')
	{
		return BAD_REQUEST;
	}

	m_checked_state = CHECK_STATE_HEADER;

	return NO_REQUEST;

}


//解析HTTP请求的一个头部信息
http_conn::HTTP_CODE http_conn::parse_headers(char* text)
{
	//printf("开始分析HTTP请求头部信息\n");
	//遇到空行表示头部字段解析完毕
	if(text[0] == '\0')
	{
		//如果HTTP请求有消息体,则还需要读取 m_content_length 字节的消息体,状态机转移到 CHECK_STATE_CONTEN
		//T 状态
		if(m_content_length != 0)
		{
			m_checked_state = CHECK_STATE_CONTENT;
			return NO_REQUEST;
		}

		//否则说明我们已经得到了一个完整的HTTP请求
		return GET_REQUEST;
	}

	//处理connection 头部字段
	else if(strncasecmp(text,"Connection:",11) == 0)
	{
		text += 11;
		text += strspn(text," \t");
		if(strcasecmp(text,"keep-alive") == 0)
		{
			m_linger = true;
		}
	}

	//处理Content-Length头部字段
	else if(strncasecmp(text,"Content-Length:",15) == 0)
	{
		printf("content-length\n");
		text += 15;
		text += strspn(text," \t");
		m_content_length = atol(text);
	}

	//处理Host头部字段
	else if(strncasecmp(text,"Host:",5) == 0)
	{
		printf("Host:");
		text += 5;
		text += strspn(text," \t");
		m_host = text;
	}
	else 
	{
		printf("oop! unknow header %s\n",text);
	}

	//printf("HTTP请求头部解析完成\n");
	return NO_REQUEST;
}

//我们没有真正解析HTTP请求的消息题,只是判断它是否被完整的读入了
http_conn::HTTP_CODE http_conn::parse_content(char* text)
{
	if(m_read_idx >= (m_content_length + m_checked_idx))
	{
		text[m_content_length] = '\0';
		
		return GET_REQUEST;
	}

	return NO_REQUEST;
}

//主状态机  没有细读
http_conn::HTTP_CODE http_conn::process_read()
{
	LINE_STATUS line_status = LINE_OK;
	HTTP_CODE ret = NO_REQUEST;
	char* text = 0;
	while(((m_checked_state == CHECK_STATE_CONTENT) && line_status == LINE_OK) || 
			((line_status = parse_line()) == LINE_OK))
	{

		text = get_line();
		m_start_line = m_checked_idx;
		printf("got 1 htp line: %s\n",text);

		switch(m_checked_state)
		{
			case CHECK_STATE_REQUESTLINE:
				{
					ret = parse_request_line(text);
					printf("REQUESTLINE\n");
					if( ret == BAD_REQUEST)
					{
						printf("BAD_REQUEST\n");
						return BAD_REQUEST;
					}
					break;
				}
			case CHECK_STATE_HEADER:
				{
					printf("HEADER\n");
					ret = parse_headers(text);
					if(ret == BAD_REQUEST)
					{
						printf("BAD_REQUEST\n");
						return BAD_REQUEST;
					}
					else if(ret == GET_REQUEST)
					{
						printf("GET_RE\n");
						return do_request();
						//return GET_REQUEST;
					}
					break;
				}
			case CHECK_STATE_CONTENT:
				{
					printf("CONTENT\n");
					ret = parse_content(text);
					if(ret == GET_REQUEST)
					{
						printf("do_read\n");
						return do_request();
					}
					line_status = LINE_OPEN;
					break;
				}
			default:
				{
					printf("INT\n");
					return INTERNAL_ERROR;
				}
		}
	}
	printf("NO_REQUEST\n");
	return NO_REQUEST;
}

//当得到一个完整,正确的HTTP请求时,我们就分析目标文件的属性,如果目标文件存在,对所有用户可读,且不是目录,则使用mmap将其映射到内存地址 m_file_address 处,并告诉调用这获取文件成功
http_conn::HTTP_CODE http_conn::do_request()
{
	//doc_root 为资源根目录
	strcpy(m_real_file,doc_root);
	int len = strlen(doc_root);
	strncpy(m_real_file + len,m_url,FILENAME_LEN - len - 1) ;
	
	if(stat(m_real_file,&m_file_stat) < 0)
	{
		return NO_REQUEST;
	}

	if(!(m_file_stat.st_mode & S_IROTH))
	{
		return FORBIDDEN_REQUEST;
	}

	if(S_ISDIR(m_file_stat.st_mode))
	{
		printf("do_read BAD_REQUEst\n");
		return BAD_REQUEST;
	}

	int fd = open(m_real_file,O_RDONLY);
	m_file_address = (char*)mmap(0,m_file_stat.st_size,PROT_READ,MAP_PRIVATE,fd,0);
	close(fd);

	return FILE_REQUEST;
}

//堆内存映射区执行 munmap 操作
void http_conn::unmap()
{
	if(m_file_address)
	{
		munmap(m_file_address,m_file_stat.st_size);
		m_file_address = 0;
	}
}

//写HTTP 响应
bool http_conn::write()
{
	int temp = 0;
	int bytes_have_send = 0;
	int bytes_to_send = m_write_idx;
	if(bytes_to_send == 0)
	{
		modfd(m_epollfd,m_sockfd,EPOLLIN);
		init();
		return true;
	}

	while(1)
	{
		temp = writev(m_sockfd,m_iv,m_iv_count);
		if(temp <= -1)
		{
			//如果TCP写缓冲没有空间,则等待下一轮EPOLLIN事件,虽然再次期间,服务器无法立即
			//接收到通一客户的下一个请求,但这可以保证连接的完整性
			if(errno == EAGAIN)
			{
				modfd(m_epollfd,m_sockfd,EPOLLOUT);
				return true;
			}
			unmap();
			return false;
		}

		bytes_to_send -= temp;
		bytes_have_send += temp;
		if(bytes_to_send <= bytes_have_send)
		{
			//发送HTTP响应成功,根据HTTP请求中的CONNection字段决定是否立即关闭连接
			unmap();
			if(m_linger)
			{
				init();
				modfd(m_epollfd,m_sockfd,EPOLLIN);
				return true;
			}
			else
			{
				modfd(m_epollfd,m_sockfd,EPOLLIN);
				return false;
			}
		}

	}
}


//往写缓冲中写入待发送的数据
bool http_conn::add_response(const char* format,...)
{
	if(m_write_idx >= WRITE_BUFFER_SIZE)
	{
		return false;
	}

	va_list arg_list;
	va_start(arg_list,format);
	int len = vsnprintf(m_write_buf + m_write_idx,WRITE_BUFFER_SIZE - 1 - m_write_idx,format,arg_list);

	if(len >= (WRITE_BUFFER_SIZE - 1 - m_write_idx))
	{
		return false;
	}

	m_write_idx += len;
	va_end(arg_list);

	return true;
}

bool http_conn::add_status_line(int status,const char* title)
{
	return add_response("%s %d %s\r\n","HTTP/1.1",status,title);
}

bool http_conn::add_headers(int content_len)
{
	add_content_length(content_len);
	add_linger();
	add_blank_line();

	return true;
}

bool http_conn::add_content_length(int content_len)
{
	return add_response("Content-Length: %d\r\n",content_len);
}

bool http_conn::add_linger()
{
	return add_response("Connection: %s\r\n",(m_linger == true) ? "keep-alive" : "close");
}

bool http_conn::add_blank_line()
{
	return add_response("%s","\r\n");
}

bool http_conn::add_content(const char* content)
{
	return add_response("%s",content);
}

//根据服务器HTTP请求的结果,决定返回给客户端的内容
bool http_conn::process_write(HTTP_CODE ret)
{
	switch(ret)
	{
		case INTERNAL_ERROR:
			{
				add_status_line(500,error_500_title);
				add_headers(strlen(error_500_form));
				if(!add_content(error_500_form))
				{
					printf("INTERNAL_ERROR\n");
					return false;
				}
				else printf("INTERNAL_ERROR 成功\n");
				break;
			}
		case BAD_REQUEST:
			{
				add_status_line(400,error_400_title);
				if(add_headers(strlen(error_400_form)))
				{
					printf("BADREQUEST\n");
					return false;
				}
				else printf("BAD_REQUEST 成功\n");
				break;
			}
		case NO_RESOURCE:
			{
				add_status_line(404,error_404_title);
				add_headers(strlen(error_404_form));
				if(!add_content(error_404_form))
				{
					printf("NO_RESOURCE\n");
					return false;
				}
				else printf("NO_RESOURCE 成功\n");
				break;
			}
		case FORBIDDEN_REQUEST:
			{
				add_status_line(403,error_403_title);
				add_headers(strlen(error_403_form));
				if(!add_content(error_403_form))
				{
					printf("FORBIDDEN_REQUEST\n");
					return false;
				}
				else printf("FORBID 成功\n");
				break;
			}
		case FILE_REQUEST:
			{
				add_status_line(200,ok_200_title);
				if(m_file_stat.st_size != 0)
				{
					add_headers(m_file_stat.st_size);
					m_iv[0].iov_base = m_write_buf;
					m_iv[0].iov_len = m_write_idx;
					m_iv[1].iov_base = m_file_address;
					m_iv[1].iov_len = m_file_stat.st_size;
					m_iv_count = 2;
					printf("FILE_RE 成功\n");
					return true;
				}
				else
				{
					const char* ok_string = "<html><body></body></html>";
					add_headers(strlen(ok_string));
					if(!add_content(ok_string))
					{
						printf("FILE_REQUEST\n");
				
						return false;
					}
					else printf("FILE___成功\n");
					
				}
			}
		default:
			{
				printf("都不是\n");
				return false;
			}
	}

	m_iv[0].iov_base = m_write_buf;
	m_iv[0].iov_len = m_write_idx;
	m_iv_count = 1;

	return true;
}

//由线程池中的工作线程调用,这是处理HTTP请求的入口函数
void http_conn::process()
{
	printf("procsee\n");
	printf("解析HTTP请求\n");
	HTTP_CODE read_ret = process_read();
	if(read_ret == NO_REQUEST)
	{
		modfd(m_epollfd,m_sockfd,EPOLLIN);
		return ;
	}
	printf("填充HTTP应答\n");
	bool write_ret = process_write(read_ret);
	if(!write_ret)
	{
		printf("填充应答失败\n");
		close_conn();

	}
	else printf("填充应答成功\n");
	modfd(m_epollfd,m_sockfd,EPOLLOUT);
}
