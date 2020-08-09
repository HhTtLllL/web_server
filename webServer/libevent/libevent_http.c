//##################################################################
// File Name: libevent_http.c
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年02月16日 星期日 13时39分03秒
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
#include "libevent_http.h"
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>

#define _HTTP_CLOSE_ "Connection: close\r\n";

//listener 这个参数evconnlistener_new_bind 已经赋值了,就是他的返回值
//fd  通信的描述符
//sa 客户端的IP和端口信息
void listener_cb(struct evconnlistener* listener,evutil_socket_t fd,
		struct sockaddr* sa,int socklen,void *user_data)
{
	printf("***********begin call******%s\n".__FUNCTION__);
	struct event_base* base = user_data;
	struct bufferevent* bev;
	printf("fd = %d\n",fd);

	//把 fd 封装成 bufferevent事件
	bev = bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE);
	if(!bev)
	{
		fprintf(stderr,"Error constructing bufferevent!");
		event_base_loopbreak(base);
		return ;
	}
	
	//将缓冲区的数据强制刷出
	bufferevent_flush(bev,EV_READ | EV_WRITE,BEV_NORMAL);
	
	//设置回调
	//读回调,写回调为NULL,事件回调,NULL 为参数给事件回调
	bufferevent_setcb(bev,conn_readcb,NULL,conn_eventcb,NULL);
	//启用读回调和写回调,写回调默认被调用,写回调不默认
	bufferevent_enable(bev,EV_READ | EV_WRITE);
	
	printf("****** end call *****%s\n",__FUNCION__);

}
//user_data  为传入的参数
void conn_readcb(struct bufferevent* bev,void *user_data)
{
	printf("****** begin call %s ....\n",__FUNCTION__);
	char buf[4096] = {0};
	char method[50],path[4096],protocol[32];
	//从缓冲区读数据
	bufferevent_read(bev,buf,sizeof(buf));
	printf("buf[%s]\n",buf);
	sscanf(buf,"%[^ ] %[^ ] %[^ \r\n]",method,path,protocol);
	printf("method[%s],path[%s],protocol[%s]\n",methon,path,protocol);
	if(strcasecmp(method,"GET") == 0)
	{
		response_http(bev,method,path);
	}

	printf("***** end call %s....\n",__FUNCTION__);
}
