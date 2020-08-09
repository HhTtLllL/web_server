#pragma once

#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <memory>
#include <functional>
#include <string>
#include "noncopyable.h"
#include "CountDownLatch.h"

namespace tt{

class Thread : noncopyable{

public:
	typedef std::function<void ()> ThreadFunc;

	explicit Thread(ThreadFunc func, const std::string& name = std::string());
	~Thread();

	void start();
	int join();

	bool started() const { return m_started; }
	pid_t tid() const { return m_tid; }
	const std::string& name()const  { return m_name; }

private:
	void setDefaultName();

	bool m_started;
	bool m_joined;

	pthread_t m_pthreadId;
	pid_t m_tid;
	ThreadFunc m_func; //线程回调函数
	std::string m_name;

	CountDownLatch m_latch; 
};

}
