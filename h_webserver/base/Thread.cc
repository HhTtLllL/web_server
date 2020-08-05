#include <assert.h>
#include <errno.h>
#include <linux/unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <memory>

#include "Thread.h"
#include "CurrentThread.h"
#include <iostream>

namespace tt{

namespace detail{
	pid_t gettid(){
		return static_cast<pid_t>(::syscall(SYS_gettid));
	}


	void CurrentThread::cacheTid(){
		if(t_cachedTid == 0){
			t_cachedTid = detail::gettid();

			t_tidStringLength = snprintf(t_tidString,sizeof(t_tidString), "%5d",t_cachedTid);
		}
	}

	

	struct ThreadData{
		typedf tt::Thread::ThreadFunc m_ThreadFunc;
		ThreadFunc m_func;
		string m_name;
		pid_t* m_tid;
		CountDownLatch* m_latch;

		
		ThreadData(ThreadFunc func,const string& name,
				pid_t* tid,
				CountDownLatch* latch)
			:m_func(func),
			m_name(name),
			m_tid(tid),
			m_latch(latch){
			
		}

		void runInThread(){
			*m_tid = tt::CurrentThread::tid();
			m_tid = NULL;
			m_latch->countDown();
			m_latch = NULL;
			
			tt::CurrentThread::t_threadName = m_name.empty() ? "tt_Thread" : m_name.c_str();

			::prctl(PR_SET_NAME,tt::CurrentThread::t_threadName);

	/*		try{
				m_func();
				tt::CurrentThread::t_threadName = "finish";
			}catch (const Exception& ex){
*/
			m_func();
			tt::CurrentThread::t_threadName = "finish";
		}
	};

	
	void* startThread(void* obj){
		ThreadData* data = static_cast<ThreadData*>(obj);

		data->runInThread;

		delete data;

		return NULL;
	}
} //detail 
	/*bool CurrentThread::isMainThread(){
		return tid() == m;
	}*/

	Thread::Thread(ThreadFunc func,const std::string& name)
		:m_started(false),
		m_joined(false),
		m_pthreadId(0),
		m_tid(0),
		m_func(func),
		m_name(name),
		m_latch(1){

		setDefaultName();
	}

Thread::~Thread(){
	if(m_started && !m_joined) pthread_detach(m_pthreadId);
}

void Thread::setDefaultName(){
	if(m_name.empty()){
		char buf[32];

		snprintf(buf,sizeof(buf),"Thread");

		m_name = buf;
	}
}


void Thread::start(){
	assert(!m_started);
	m_started = true;

	detail::ThreadData* data = new detail::ThreadData(m_func,m_name,&m_tid,&m_latch);
	
	if(pthread_create(&m_pthreadId,NULL,&detail::startThread,data)){
		m_started = false;
		delete data;
	}else{
		m_latch.wait();
		assert(m_tid>0);
	}

}

int Thread::join(){
	assert(m_started);
	assert(!m_joined);
	m_joined = true;

	return pthread_join(m_pthreadId,NULL);
}

}

