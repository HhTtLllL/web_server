//##################################################################
// File Name: main.c
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年02月14日 星期五 03时56分25秒
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
#include "epoll_server.h"

int main(int argc,char *argv[])
{
	int port;
	int ret;
	if(argc < 3)
	{
		//printf("eg: ./a.out port path\n");
		//exit(1);
		port = 8080;
		
		ret = chdir("../dir");
		if(ret == -1)
		{
			perror("chdir error");
			exit(1);
		}

	}
	else
	{
		//将端口转为 数字
		port = atoi(argv[1]);
		
		//修改进程的工作目录,方便后续进行操作
		ret = chdir(argv[2]);
		if(ret == -1)
		{
			perror("chdir error");
			exit(1);
		}

	}

	//启动epoll模型
	epoll_run(port);

	return 0;
}

