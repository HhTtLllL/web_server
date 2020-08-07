#include "Epoll.h"
#include <assert.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <deque>
#include <queue>
#include "Util.h"
#include "base/Logging.h"

#include <arpa/inet.h>
#include <iostream>

using namespace tt;

const int EVENTSNUM = 4096;
const EPOLLWAIT_TIME = 10000;

typedef shared_ptr<Channel> SP_Channel;

Epoll::Epoll()
	:m_epollFd(epoll_create1(EPOLL_CLOEXEC)),
	m_events(EVENTSNUM){
	
	assert(m_epollFd > 0);	
}

Epoll::~Epoll() {}


//注册新描述符
void Epoll::epoll_add(SP_Channel request, int timeout){
	
	int fd = request->getFd();

	if(timeout > 0){
		add_timer(request, timeout);
		m_fd2http[fd] = request->getHolder();
	}


	struct epoll_event event;
	
	event.data.fd = fd;
	event.events  =request->getEvents();
	
	request->EqualAndUpdateLastEvents();
	m_fd2chan[fd] = request;

	if(epoll_ctl(m_epollFd, EPOLL_CTL_ADD, fd, &event) < 0){
		perror("epoll_add error");
		m_fd2chan[fd].reset();
	}

}


//修改描述符状态
void Epoll::epoll_mod(SP_Channel request, int timeout){
	
	if(timeout > 0) add_timer(request,timeout);

	int fd = request->getFd();
	if(!request->EqualAndUpdateLastEvents()){
		struct epoll_event event;

		event.data.fd = fd;
		event.events = request->getEvents();
		if(epoll_ctl(m_epollFd, EPOLL_CTL_MOD, fd, &event) < 0){
			perror("epoll_mod error");

			m_fd2chan[fd].reset();
		}
	
	}
}


//从epoll 中删除描述符‘

void Epoll::epoll_del(SP_Channel request){
	
	int fd = request->getFd();
	
	struct epoll_event event;
	event.data.fd = fd;
	event.events = request->getLastEvents();

	if(epoll_ctl(m_epollFd, EPOLL_CTL_DEL, fd, &event) < 0){
		prror("epoll_del error");
	}

	m_fd2chan[fd].reset();
	m_fd2http[fd].reset();
}

//返回活跃事件数
std::vector<SP_Channel> Epoll::poll(){
	
	while(true){
		
		int event_count = 
			epoll_wait(m_epollFd, &*m_events.begin(),m_events.size(), EPOLLWAIT_TIME);
	
		if(event_count < 0) perror("epoll wait error");

		std::vector<SP_Channel> req_data = getEventsRequest(event_count);

		if(req_data.size() > 0) return req_data;
	}
}


void Epoll::handleExpired() { m_timeManager.handleExpiredEvent(); }


//分发处理函数
std::vector<SP_Channel> Epoll::getEventsRequest(int events_num){

	std::vector<SP_Channel> req_data;

	for( int i = 0 ; i < events_num ; ++ i ){

		//获取有事件产生的描述符
		int fd = m_events[i].data.fd;

		SP_Channel cur_req = m_fd2chan[fd];
		
		if(cur_req){
			
			cur_req->setRevents(m_events[i].events);
			cur_req->setEvents(0);

			//加入线程池之前将 Timer 和 request 分离
			
			//cur_req->seperateTimer();

			req_data.push_back(cur_req);
		}else{
			LOG << "SP cur_req is invaild";
		
		}
	}

	return req_data;
}


void Epoll::add_timer(SP_Channel request_data, int timeout){
	
	shared_ptr<HttpData> t = request_data->getHolder();

	if(t) m_timeManager.addTimer(t,timeout);
	else LOG << "timer add fail";
}
