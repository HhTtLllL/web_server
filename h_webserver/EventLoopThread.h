#ifndef TT_NET_EVENTLOOPTHREAD_H
#define TT_NET_EVENTLOOPTHREAD_H


#include "EventLoop.h"
#include "base/Condition.h"
#include "base/MutexLock.h"
#include "base/Thread.h"
#include "base/noncopyable.h"


namespace tt{

namespace net{
class EventLoopThread : noncopyable{
	
public:
	EventLoopThread();
	~EventLoopThread();

	EventLoop* startLoop();


private:

	void threadFunc();
	EventLoop* m_loop;
	bool m_exiting;
	Thread m_thread;
	MutexLock m_mutex;
	Condition m_cond;

};

}
}// tt



#endif
