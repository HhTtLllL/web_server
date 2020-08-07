#ifndef TT_NET_EPOLL_H
#define TT_NET_EPOLL_H

#include <sys/epoll.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Channel.h"
#include "HttpData.h"
#include "Timer.h"

namespace tt{

class Epoll{
	
public:

	Epoll();
	~Epoll();

	void epoll_add(SP_Channel requsest, int timeout);
	void epoll_mod(SP_Channel requsest, int timeout);
	void epoll_del(SP_Channel requsest);


	std::vector<std::shared_ptr<Channel> > poll();
	std::vector<std::shared_ptr<Channel> > getEventsRequest(int events_num);

	void add_timer(std::shared_ptr<Channel> request_data, int timeout);
	int getEpollfd() { return m_epollFd; }
	void handleExpired();



private:

	static const int MAXFDS = 100000;

	int m_epollFd;

	std::vector<epoll_event> m_events;
	std::shared_ptr<Channel> m_fd2chan[MAXFDS];
	std::shared_ptr<HttpData> m_fd2http[MAXFDS];

	TimerMannager m_timeManager;
};




#define 
