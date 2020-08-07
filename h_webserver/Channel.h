#ifndef TT_NET_CHANNEL_H
#define TT_NET_CHANNEL_H

#include "../noncopyable.h"
#include <sys/epoll.h>
#include <sys/epoll.h>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "Timer.h"


namespace tt{

namespace net{
	
class EventLoop;
class HttpData;


class Channel : noncopyable{

public:
	Channel(EventLoop *loop);
	Channel(EventLoop *loop, int fd);
	~Channel();
	int getFd();
	void setFd(int fd);


	void setHolder(std::shared_ptr<HttpData> holder)  { m_holder = holder; }

	std::shared_ptr<HttpData> getHolder(){
		std::shared_ptr<HttpData> ret(m_holder.lock());

		return ret;
	}


	void setReadHandler(CallBack &&readHandler) { m_readHandler = readHandler; }
	void setWriteHandler(CallBack &&writeHandler) { m_writeHandler = writeHandler; }
	void setErrorHandler(CallBack &&errorHandler) { m_errorHandler = errorHandler; }
	void setConnHandler(CallBack &&connHandler) { m_connHandler = connHandler; }


	void handleEvents(){
		
		m_events = 0;
		
		if((m_revents & EPOLLHUP) && !(m_revents & EPOLLIN)){
			m_events = 0;

			return ;
		}

		if(m_revents & EPOLLERR){
			if(m_errorHandler) m_errorHandler();

			m_events = 0;

			return ;
		}

		if(m_revents & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)){
			handleRead();
		}

		if(m_revents & EPOLLOUT){
			handleWrite();
		}

		handleConn();
	}


	void handleRead();
	void handleWrite();
	void handleError(int fd, int err_num, std::string short_msg);
	void handleConn();


	void setRevents(__uint32_t ev) { m_revents = ev; }
	void setEvents(__uint32_t ev) { m_events = ev; }

	__uint32_t& getEvents() {return m_events; }

	bool EqualAndUpdateLastEvents(){
		bool ret = (m_lastEvents == m_events);

		m_lastEvents = m_events;

		return ret;
	}

	__uint32_t getLastEvents() { retur m_lastEvents; }






private:
	typedef std::function<void()> CallBack;
	EventLoop *m_loop;
	int m_fd;
	__uint32_t m_events;
	__uint32_t m_revents;
	__uint32_t m_lastEvents;


	//方便找到上层持有该 Channel 的对象
	std::weak_ptr<HttpData> m_holder;



private:
	int parse_URI();
	int parse_Headers();
	int analyisRequest();


	CallBack m_readHandler;
	CallBack m_writeHandler;
	CallBack m_errorHandler;
	CallBack m_connHandler;







};

typedef std::shared_ptr<Channel> SP_Channel;





}  //net


}// tt
