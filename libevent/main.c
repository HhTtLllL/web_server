//##################################################################
// File Name: main.c
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年02月16日 星期日 13时16分57秒
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

int main(int argc,char **argv)
{
	if(argc < 3)
	{
		printf("./event_http port path\n");
		return -1;
	}

	if(chdir(argv[2]) < 0)
	{
		printf("dir is not exists:%s\n",argv[2]);
		perror("chdir err:");
		return -1;
	}
	//创建一个事件处理框架
	struct event_base *base;
	struct evconnlistener* listener;
	struct event *signal_event;

	struct sockaddr_in sin;
	base = event_base_new();

	if(!base)
	{
		fprintf(stderr,"Could not initialize libevent!\n");
		return 1;
	}

	memset(&sin,9,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(argv[1]));
	//这里没有设置IP,因为 ADD_INY  为0,这里memset 之后也是0,所以不用设置

	//创建监听的套接字,绑定,监听,接受连接请求
	//base 事件处理框架,    (void*) base,参数传递,将base 作为参数传入listener_cb 回调中,     -1,listener的backlog ,代表 128  
	listener = evconnlistener_new_bind(base,listener_cb,(void*)base,LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,-1,(struct sockaddr*)&sin,sizeof(sin));

	if(!listener)
	{
		fprintf(stderr,"Could not create a listener!\n");
		return 1;
	}

	//创建信号事件,捕捉并处理
	//SIGINT  为要捕捉的信号,signal_cb 为当捕捉到这个信号是对应的动作
	signal_event = evsignal_new(base,SIGINT,signal_cb,(void*)base);

	if(!signal_event || event_add(signal_event,NULL) < 0)
	{
		fprintf(stderr,"Could not create a listener!\n");
		return 1;
	}

	//事件循环
	event_base_dispatch(base);

	//资源释放
	evconnlistener_free(listener);
	event_free(signal_event);
	event_base_free(base);

	printf("done\n");

	return 0;
}

