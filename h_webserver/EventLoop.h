#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <vector>
//#include "Channel.h"
//#include "Epoll.h"
#include "Util.h"
#include "base/CurrentThread.h"
#include "base/Logging.h"
#include "base/Thread.h"



//using namespace tt;
//using namespace net;



/*
namespace tt::net{

	class Channel;
}
*/
namespace tt{

namespace net{

class Channel;
class Epoll;

class EventLoop{

public:
	typedef std::function<void()> Functor;

	EventLoop();
	~EventLoop();

	void loop();    //Loops forever 
	void quit();

	void runInLoop(Functor&& cb);
	void queueInLoop(Functor&& cb);

	bool isInLoopThread() const { return m_threadId == CurrentThread::tid(); }

	void assertInLoopThread(){ assert(isInLoopThread()); }
	void shutdown(std::shared_ptr<Channel> channel);

	void removeFromPoller(std::shared_ptr<Channel> channel);

	void updatePoller(std::shared_ptr<Channel> channel, int timeout = 0);
	void addToPoller(std::shared_ptr<Channel> channel, int timeout = 0); 


private:
	bool m_looping;  //是否处于循环
	bool m_quit;   //是否停止
	bool m_eventHandling;   //eventhandling 是否正在处理event 事件
	bool m_callingPendingFunctors;  //是否正在嗲偶偶那个pendingFunctor 的函数


	std::shared_ptr<Epoll> m_epoll;
	int m_wakeupFd;
	mutable MutexLock m_mutex;
	std::vector<Functor> m_pendingFunctors;
	std::shared_ptr<Channel> m_wakeupChannel;
	const pid_t m_threadId;

	void wakeup();
	void handleRead();
	void doPendingFunctors();
	void handleConn();

};
	


}

}
