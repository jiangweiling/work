#ifndef SOCKET_EPOLL
#define SOCKET_EPOLL
#include "socket_ns.h"

namespace socket_ns {

class SocketEpoll {
private:
	int m_size;
	int m_epfd;
	struct epoll_event m_ep_event;
public:
	SocketEpoll();
	SocketEpoll(int size = 256); //默认参数在函数声明处给出，在函数定义按照无默认参数方式定义函数
	SocketEpoll(const SocketEpoll& se) = delete;
	SocketEpoll(SocketEpoll&& se);
	~SocketEpoll();

	SocketEpoll operator= (const SocketEpoll& se) = delete;
	SocketEpoll operator= (SocketEpoll&& se);

};

};

#endif
