//##################################################################
// File Name: epoll_server.c
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年02月14日 星期五 04时00分38秒
//=============================================================
//!/usr/bin/python

#include <sys/socket.h>
#include <netinet/in.h>
#include <assert.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/epoll.h>
#include <dirent.h>
#include <ctype.h>
#include "epoll_server.h"
#define MAXSIZE 2000

void epoll_run(int port)
{
	//创建线程池
	
	//创建一个epoll树的根结点
	int epfd = epoll_create(MAXSIZE);
	if(epfd == -1)
	{
		perror("epoll_create error");
		exit(1);
	}

	//添加要监听的结点
	//先添加监听的lfd
	int lfd = init_listen_fd(port,epfd);
	
	//委托内核监测添加到树上的结点
	struct epoll_event all[MAXSIZE];
	while(1)
	{
		int ret = epoll_wait(epfd,all,MAXSIZE,-1);
		if(ret == -1)
		{
			perror("epoll_wait error");
			exit(1);
		}

		//遍历发生变化的结点
		for(int i = 0;i < ret;i++)
		{
			//只处理读事件
			struct epoll_event* pev = &all[i];
			if(!(pev->events & EPOLLIN))
			{
				//不是读事件
				continue;
			}
			//lfd 监听套接字
			if(pev->data.fd == lfd)
			{
				//接受连接请求
				do_accept(lfd,epfd);
			}
			else
			{
				//读数据
				do_read(pev->data.fd,epfd);
			}
			

		}
	}

	printf("........\n");
}

//初始化监听套接字
int init_listen_fd(int port,int epfd)
{
	//创建监听套接字
	int lfd = socket(AF_INET,SOCK_STREAM,0);
	if(lfd == -1)
	{
		perror("socket lfd error");
		exit(1);
	}

	//lfd绑定本地IP和port
	struct sockaddr_in serv;
	memset(&serv,0,sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	//端口复用
	int flag = 1;
	setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));

	int ret = bind(lfd,(struct sockaddr*)&serv,sizeof(serv));
	if(ret == -1)
	{
		perror("bind error");
		exit(1);
	}

	//设置监听
	ret = listen(lfd,64);
	if(ret == -1)
	{
		perror("listen error");
		exit(1);
	}
	
	//将lfd  添加到 epoll 树上
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = lfd;
	ret = epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);

	if(ret == -1)
	{
		perror("epoll_ctl error");
		exit(1);
	}


	return lfd;
}

//接受连接请求
void do_accept(int lfd,int epfd)
{
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	int cfd = accept(lfd,(struct sockaddr*)&client,&len);
	if(cfd == -1)
	{
		perror("accept error");
		exit(1);
	}

	//打印客户端信息
	char ip[64] = {0};
	//inet_ntop  对大端整形进行一个转化
	printf("New Client IP:%s,Port:%d,cfd = %d\n",inet_ntop(AF_INET,&client.sin_addr.s_addr,ip,sizeof(ip)),ntohs(client.sin_port),cfd);
	
	//设置cfd 为非阻塞
	int flag = fcntl(cfd,F_GETFL);
	flag |+ O_NONBLOCK;
	fcntl(cfd,F_SETFL,flag);


	//将结点挂在epoll 树上
	struct epoll_event ev;
	ev.data.fd = cfd;
	ev.events = EPOLLIN | EPOLLET; //EPOLLET  边缘非阻塞
	int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);
	if(ret == -1)
	{
		perror("epoll_ctl add cfd error");
		exit(1);
	}

	return ;
}
//读数据
void do_read(int cfd,int epfd)
{
	//将游览器发送的数据读取
	char line[1024] = {0};
	//第一次读取请求行
	int len = get_line(cfd,line,sizeof(line));
	if(len == 0)
	{
		printf("客户端断开连接...\n");
		//关闭套及诶子,删除结点
		disconnect(cfd,epfd);

	}
	else if(len == -1)
	{
		//关闭套及诶子,删除结点
		perror("recv error");
		exit(1);
	}
	/*else
	{
		//输出请求行的数据
		printf("请求行: %s",line);
		//还有数据
		//继续读
		while(len)
		{
			char buf[1024] = {0};
			len = get_line(cfd,buf,sizeof(buf));
			printf("len = %d,sizeof(buf) = %ld\n",len,sizeof(buf));
			printf("======请求头==asdasdasdas====");
			printf("--:%s ---len = %d\n",buf,len);
		}

	}
	*/
	//请求行: GET /xxxx HTTP/1.1
	//判断是否为 GET
	//比较前n个字符,不区分大小写
	printf("即将进入http请求处理\n");
	printf("line = %s\n",line);
	if(strncasecmp("GET",line,3) == 0)
	{
		//处理http请求
		http_request(line,cfd);
		printf("进入http请求\n");
	//	disconnect(cfd,epfd);
	}

	

}


//解析http请求消息的每一行内容
int get_line(int sock,char* buf,int size)
{
	int i = 0;
	char c = '\0';
	int n;
	while((i < size - 1) && (c != '\n'))
	{
		//每次读取一个字节
		//printf("阻塞\n");
		n = recv(sock,&c,1,0);
		//printf("判断阻塞\n");
		//判断是否成功读取
		if(n > 0)
		{
			if(c == '\r')
			{
				n = recv(sock,&c,1,MSG_PEEK);
				if((n > 0) && (c == '\n'))
				{
					recv(sock,&c,1,0);
				}
				else
				{
					c = '\n';
				}
			}

			buf[i] = c;
			i++;
		}
		else
		{
			c = '\n';
		}
	}

	buf[i] = '\0';
	
	if(n == -1) i = -1;
	

	return i;
}


//http请求处理
void http_request(const char* request,int cfd)
{
	//拆分 http 请求行
	char method[12],path[1024],protocol[12];
	sscanf(request,"%[^ ] %[^ ] %[^ ]",method,path,protocol);
	
	printf("method:%s\npath=%s\nprotoclo=%s\n",method,path,protocol);

	//处理path   /xxxxx
	char* file = path + 1;
	
	//转码  将不能识别的中文乱码转为 中文
	decode_str(path,path);
	//解码 

	
	//printf("wwwwwww--------%s--------\n",path);
	//如果没有指定访问的资源,默认显示资源目录中的内容
	if(strcmp(path,"/") == 0)
	{
		//file 指向资源目录的当前位置
		file = "./";
	}

	//获取文件属性
	struct stat st;
	int ret = stat(file,&st);
	if(ret == -1)
	{
		//show  404
		//perror("stat error");
		//exit(1);
		send_respond_head(cfd,404,"File Not Found",".html",-1);
		send_file(cfd,"404.html");
		return ;
	}
	//判断是目录还是文件  stat
	//如果是目录
	if(S_ISDIR(st.st_mode))
	{
		//将目录的内容和一个 html网页,发送
		//首先发送头信息
		send_respond_head(cfd,200,"OK",get_file_type(".html"),-1);
		//发送目录信息
		send_dir(cfd,file);
	}
	else if(S_ISREG(st.st_mode))   //文件
	{
		//发送消息抱头
		send_respond_head(cfd,200,"OK",get_file_type(file),st.st_size);
		//打开文件,将文件发送给游览器
		send_file(cfd,file);
	}


}


//断开链接的函数
void disconnect(int cfd,int epfd)
{
	int ret = epoll_ctl(epfd,EPOLL_CTL_DEL,cfd,NULL);
	if(ret == -1)
	{
		perror("epoll_ctl del cfd error");
		exit(1);
	}

	close(cfd);
}

//发送http 消息包头            no: 状态码
void send_respond_head(int cfd,int no,const char* desp,const char* type,long len)
{
	char buf[1024] = {0};
	//状态行
	sprintf(buf,"HTTP/1.1 %d %s\r\n",no,desp);
	send(cfd,buf,strlen(buf),0);
	//消息报头
	sprintf(buf,"Content-Type:%s\r\n",type);
	sprintf(buf + strlen(buf),"Content-Length:%ld\r\n",len);
	send(cfd,buf,strlen(buf),0);
	send(cfd,"\r\n",2,0);

	return ;
}

void send_file(int cfd,const char* filename)
{
	//打开文件
	int fd = open(filename,O_RDONLY);
	if(fd == -1)
	{
		//show 404
		send_respond_head(cfd,404,"File Not Found",".html",-1);
		send_file(cfd,"404.html");
		return ;
	}

	//循环读文件
	char buf[4096] = {0};
	int len = 0;
	while((len = read(fd,buf,sizeof(buf))) > 0)
	{
		//发送读出的数据
		send(cfd,buf,len,0);
	}
	
	if(len == -1)
	{
		perror("read filename error");
		exit(1);
	}

	close(fd);
	return ;
}


void send_dir(int cfd,const char* dirname)
{
	char enstr[1024] = {0};
	char path[1024] = {0};
	//拼一个html页面 <table></table>
	char buf[4096] = {0};
	sprintf(buf,"<html><head><title>目录名:%s</title></head>",dirname);
	sprintf(buf + strlen(buf),"<body><h1>当前目录:%s</h1><table>",dirname);
	
	
	//目录项指针
	struct dirent** ptr;
	int num = scandir(dirname,&ptr,NULL,alphasort);
	if(num == -1)
	{
		//perror("scandir error");
		//exit(1);
		//show 404
		send_respond_head(cfd,404,"File Not Found",".html",-1);
		send_file(cfd,"404.html");

		return ;
	}
	
	for(int i = 0;i < num;i++)
	{
		char* name = ptr[i]->d_name;
		//拼接文件的完整路径
		sprintf(path,"%s%s",dirname,name);
		printf("path = %s=======\n",path);
		struct stat st;
		stat(path,&st);
		

		encode_str(enstr,sizeof(enstr),name);
		//如果是文件
		if(S_ISREG(st.st_mode))
		{
			sprintf(buf + strlen(buf),"<tr><td><a href=\"%s\">%s</a></td><td>%ld</td></tr>",enstr,name,st.st_size);
		}
		else if(S_ISDIR(st.st_mode))//如果是目录
		{
			sprintf(buf + strlen(buf),"<tr><td><a href=\"%s/\">%s/</a></td><td>%ld</td></tr>",enstr,name,st.st_size);
		}
		send(cfd,buf,strlen(buf),0);
		memset(buf,0,sizeof(buf));
		//字符串拼接
	}

	sprintf(buf + strlen(buf),"</table></body></html>");
	send(cfd,buf,strlen(buf),0);

	printf("dir message send ok\n");
#if 0 
	DIR* dir = opendir(dirname);
	if(dir == NULL)
	{
		perror("opendir error");
		exit(1);
	}

	//读目录
	struct dirent* ptr = NULL;
	while((ptr = readdir(dir)) != NULL)
	{
		char* name = ptr->d_name;
	}
	closedir(dir);
#endif
}


/* 这里的内容是处理%20 之类的,解码过程*/
//编码  from 中文, to 编码后的字符串
void encode_str(char* to,int tosize,const char* from)
{
	int tolen;

	for(tolen = 0;*from != '\0' && tolen + 4 < tosize;++from)
	{
		//isalnum  判断是否需要编码 1-9 a-z
		///_.-~  是特殊字符,但是 http协议中 不需要转码
		//strchr--- 在from 中匹配 五个符号
		if(isalnum(*from) || strchr("/_.-~",*from) != (char*)0)
		{
			*to = *from;
			++to;
			++tolen;
		}
		else
		{
			//%% 转义,显示一个字符串  %02x  16进制的数,有2位,要是不够用 0 填充
			//(int)*from & 0xff    作用是将一个将一个字符变为 16进制,  先转十进制,在和  0xff  相&
			sprintf(to,"%%%02x",(int)*from & 0xff);
			//转完后 占 3个字节
			to += 3;
			tolen += 3;
		}
	}

	*to = '\0';
}


//解码操作
void decode_str(char* to,char* from)
{
	for(;*from != '\0';++to,++from)
	{
		//第一个字节为 % ,后两个字节上的数 是否为16进制的数
		if(from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2]))
		{
			//依次判断from 中 %20   三个字符,将16进制转化为 10进制
			*to = hexit(from[1])*16 + hexit(from[2]);
			//移过已经处理的两个字符( %21指针指向1),表达式3 的++from还会再向后移一个字符
			from += 2;
		}
		else
		{
			*to = *from;
		}
	}

	*to = '\0';
}
//将 16 进制转化为 10进制
int hexit(char c)
{
	if(c >= '0' && c <= '9') return c-'0';
	if(c >= 'a' && c <= 'f') return c - 'a' + 10;
	if(c >= 'A' && c <= 'F') return c - 'A' + 10;


	return 0;
}

const char* get_file_type(const char* name)
{
        char* dot;
        //从右向左查找 '.' 字符,如不存在返回NULL
        dot = strrchr(name,'.');
        if(dot == NULL) return "text/plain; charset=utf-8";
        if(strcmp(dot,".html") == 0 || strcmp(dot,".htm") == 0) return "text/html; charset=utf-8";
        if(strcmp(dot,".jpg") == 0 || strcmp(dot,".jpeg") == 0) return "image/jpeg";
        if(strcmp(dot,".gif") == 0) return "image/gif";
        if(strcmp(dot,".png") == 0) return "image/png";
        if(strcmp(dot,".css") == 0) return "text/css";
        if(strcmp(dot,".au") == 0) return "audio/basic";
        if(strcmp(dot,".wav") == 0) return "audio/wav";
        if(strcmp(dot,".avi") == 0) return "video/x-msvideo";
        if(strcmp(dot,".mov") == 0 || strcmp(dot,".qt") == 0) return "video/quicktime";
        if(strcmp(dot,".mpeg") == 0 || strcmp(dot,".mpe") == 0) return "video/mpeg";
        if(strcmp(dot,".vrml") == 0 || strcmp(dot,".wrl") == 0) return "video/vrml";
        if(strcmp(dot,".midi") == 0 || strcmp(dot,".mid") == 0) return "video/midi";
        if(strcmp(dot,".mp3") == 0) return "audio/mpeg";
        if(strcmp(dot,".ogg") == 0) return "application/ogg";
        if(strcmp(dot,".pac") == 0) return "application/x-ns-proxy-autoconfig";

	return "text/plain; charset=utf-8";

}

