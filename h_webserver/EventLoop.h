#pragma once

#include <iostream>
#include <vector>

namespace tt{

namespace net{

class EventLoop{

public:
	typedef std::function<void()> Functor;

	EventLoop();
	~EventLoop();

	void loop();    //Loops forever 
	void quit();

	void runInLoop(Functor cb);
	void queueInLoop(Functor cb);
	
	void assertInLoopThread(){
		
	}


private:
	bool m_looping;  //是否处于循环
	bool m_quit;   //是否停止
	bool m_eventHandling;   //eventhandling 是否正在处理event 事件
	bool m_callingPendingFunctors;  //是否正在嗲偶偶那个pendingFunctor 的函数


	shared_ptr<Epoll> m_epoll;
	int m_wakeupFd;
	mutable MutexLock m_mutex;
	std::vector<Functor> m_pendingFunctors;
	//shared_ptr<Channel> m_wakeupChannel;
	const pid_t m_threadId;

	void wakeup();
	void handleRead();
	void doPendingFunctors();
	void handleConn();




};
	


}

}
