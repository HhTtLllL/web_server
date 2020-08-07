#include "EventLoop.h"
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <iostream>
#include "Util.h"
#include "base/Logging.h"

__thread EventLoop* t_loopInTishThread = 0;

using namespace tt;
using namespace net;


int createEventfd(){

	int evtfd = eventfd(0,EFD_NONBLOCK | EFD_CLOEXEC);
	if(evtfd < 0){
		LOG << "Failed in eventfd";
		abort();
	}

	return evtfd;
}

EventLoop::EventLoop()
	:m_looping(false),
	m_epoll(new Epoll()),
	m_wakeupFd(createEventfd()),
	m_quit(false),
	m_eventHandling(false),
	m_callingPendingFunctors(false),
	m_threadId(CurrentThread::tid()),
	m_wakeupChannel(new Channel(this,m_wakeupFd)){
	
		if(t_loopInTishThread){
		
		
		}else{
			t_loopInTishThread = this;
		
		}


		m_wakeupChannel->setEvents(EPOLLIN | EPOLLET);
		m_wakeupChannel->setReadHandler(bind(&EventLoop::handleRead, this));
		m_wakeupChannel->setConnHandler(bind(&EventLoop::handleConn,this));
		m_epoll->epoll_add(m_wakeupChannel,0);
}



void EventLoop::handleConn(){
	updatePoller(m_wakeupChannel, 0);
}

EventLoop::~EventLoop(){
	
	close(m_wakeupFd);
	t_loopInTishThread = NULL;
}

void EventLoop::wakeup(){
	
	uint64_t one = 1;

	ssize_t n  = writen(m_wakeupFd, (char*)(&one), sizeof(one));

	if(n != sizeof(one)){
		LOG << "EventLoop::wakeup() writes" << n << "bytes instead of 8";
	}
}


void EventLoop::handleRead(){

	uint64_t one = 1;
	ssize_t n = readn(m_wakeupFd, &one, sizeof(one));

	if(n != sizeof(one)){
		LOG << "EventLoop::handleRead() reads " << n << "bytes instead of 8";
	}

	m_wakeupChannel->setEvents(EPOLLIN | EPOLLET);
}


void EventLoop::runInLoop(Functor&& cb){
	
	if(isInLoopThread()) cb();
	else queueInLoop(std::move(cb));

}

void EventLoop::queueInLoop(Functor&& cb){
	
	{
		MutexLockGuard lock(m_mutex);
		m_pendingFunctors.emplace_back(std::move(cb));
	}

	if(!isInLoopThread() || m_callingPendingFunctors) wakeup();

}



void EventLoop::loop(){
	
	assert(!m_looping);
	assert(isInLoopThread());

	m_looping = true;
	m_quit = false;

	std::vector<SP_Channel> ret;
	while(!m_quit){
	
		ret.clear();
		ret = m_epoll->poll();
		m_eventHandling = true;

		for( auto& it : ret) it->handleEvents();

		m_eventHandling = false;

		doPendingFunctors();
		m_epoll->handleExpired();
	}

	m_looping = false;
}

void EventLoop::doPendingFunctors(){
	
	std::vector<Functor> functors;
	m_callingPendingFunctors = true;
	
	{
		MutexLockGuard lock(m_mutex);
		functors.swap(m_pendingFunctors);
	}

	for(size_t i = 0 ; i < functors.size() ; ++ i) functors[i]();

	m_callingPendingFunctors = false;
}


void EventLoop::quit(){
	
	m_quit = true;
	if(!isInLoopThread()){
		
		wakeup();
	}
}


















































