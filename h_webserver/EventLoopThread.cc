
#include "EventLoopThread.h"
#include <functional>

using namespace tt;
using namespace net;

EventLoopThread::EventLoopThread()
	:m_loop(NULL),
	m_exiting(false), //是否退出
	m_thread(std::bind(&EventLoopThread::threadFunc,this), "EventLoopThread"),
	m_mutex(),
	m_cond(m_mutex){
	
	
}


EventLoopThread::~EventLoopThread(){
	
	m_exiting = true;
	if(m_loop != NULL){
		
		m_loop->quit();
		m_thread.join();
	}
}

EventLoop* EventLoopThread::startLoop(){

	assert(!m_thread.started());
	m_thread.start();

	{
		MutexLockGuard lock(m_mutex);

		//一直等到 htreadFun 在Thread 里真正跑起来
		
		while(m_loop == NULL) m_cond.wait();
	}

	return m_loop;
}


void EventLoopThread::threadFunc(){

	EventLoop loop;

	{
		MutexLockGuard lock(m_mutex);
		m_loop = &loop;
		m_cond.notify();
	}

	loop.loop();
	m_loop = NULL;
}

