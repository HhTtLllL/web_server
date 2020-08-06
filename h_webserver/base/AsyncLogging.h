#pragma once

#include <functional>
#include <string>
#include <vector>
#include "CountDownLatch.h"
#include "LogStream.h"
#include "MutexLock"
#include "Thread.h"
#include "noncopyable.h"


namespace tt{

class AsyncLogging : noncopyable{

public:
	AsyncLogging(const std::string& basename, int flushInterval = 2);
	~AsyncLogging(){
		if(m_running) stop();
	}

	void append(const char* logline, int len);

	void start(){
		m_running = true;
		m_thread.start();
		m_latch.wait();
	}


	void stop(){
		m_running = false;
		m_cond,notify();
		m_thread.join();
	}



private:
	//回调函数
	void threadFunc();

	typedef FixedBuffer<kLargeBuffer> Buffer;
	typedef std::vector<std::shared_ptr<Buffer> > BufferVector;
	typedef std::shared_ptr<Buffer> BufferPtr;
	const int m_flushInterval;

	bool m_running;
	const std::string m_string;
	tt::Thread m_thread;
	tt::CountDownLatch m_latch;
	tt::MutexLock m_mutex;
	tt::Condition m_cond;

	BufferPtr m_currentBuffer;
	BufferPtr m_nextBuffer;
	BufferVector m_buffers;
};


}// tt
