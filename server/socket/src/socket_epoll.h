#ifndef SOCKET_EPOLL_H
#define SOCKET_EPOLL_H
#include "socket_ns.h"
#include "socket.h"
namespace socket_ns {

typedef struct epoll_event epoll_event_t;
class SocketEpoll {
private:
	int m_size;
	int m_epfd;
	epoll_event_t* m_event_ptr;

private:
	static const int socket_event;
	static const int socket_readable;
	
public:
	SocketEpoll(int size = 256); //默认参数在函数声明处给出，在函数定义按照无默认参数方式定义函数
	SocketEpoll(const SocketEpoll& se) = delete;
	SocketEpoll(SocketEpoll&& se);
	~SocketEpoll();
	int add(const Socket& s);
	int remove(const Socket& s);
	int wait(int timeout = -1); 
	//timeout超时参数，单位毫秒，-1表示系统自行设置不确定的超时参数,0表示立刻返回
	SocketEpoll& operator= (const SocketEpoll& se) = delete;
	SocketEpoll& operator= (SocketEpoll&& se);

};

};

#endif
