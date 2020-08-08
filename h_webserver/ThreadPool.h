#ifndef TT_NET_THREADPOOL_H
#define TT_NET_THREADPOOL_H

#include "Channel.h"
#include <pthread.h>
#include <functional>
#include <memory>
#include <vector>


namespace tt{

const int THREADPOOL_INVALID = -1;
const int THREADPOOL_LOCK_FAILURE = -2;
const int THREADPOOL_QUEUE_FULL = -3;
const int THREADPOOL_SHUTDOWN = -4;
const int THREADPOOL_THREAD_FAILURE = -5;
const int THREADPOOL_GRACEFUL = 1;

const int MAX_THREADS = 1024;
const int MAX_QUEUE = 65535;

typedf enum{
	
	immdiate_shutdown = 1; // 立即关闭
	graceful_shutdown = 2; // 优雅的关闭

}ShutDownOption;

struct ThreadPoolTask{

	std::function<void(std::shared_ptr<void>)> fun;
	std::shared_ptr<void> args;

};


class ThreadPool{

public:
	static int threadpool_create(int _thread_count, int _queue_size);
	static int threadpool_add(std::shared_ptr<void> args, std::function<void(std::shared_ptr<void>)> fun);
	static int threadpool__destroy(ShutDownOption shutdown_option = graceful_shutdown);
	static int threadpool_free();

	static void *threadpool_thread(void *args);

private:
	static pthread_mutex_t lock;
	static pthread_cond_t notigy;

	static std::vector<pthread_t> threads;
	static std::vector<ThreadPoolTask> queue;
	static thread_count;
	static int queue_size;
	static int head; 

	static int tail;
	static int count;
	static shutdown;
	static started;
};

} //tt


#endif
