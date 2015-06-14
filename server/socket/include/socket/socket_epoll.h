#ifndef SOCKET_EPOLL
#define SOCKET_EPOLL
#include "socket_ns.h"

namespace socket_ns {

class SocketEpoll {
private:
	int m_epfd;
public:
	SocketEpoll();
	SocketEpoll(int size);
	SocketEpoll(const SocketEpoll& se) = delete;
	SocketEpoll(SocketEpoll&& se);
	~SocketEpoll();

	SocketEpoll operator= (const SocketEpoll& se) = delete;
	SocketEpoll operator= (SocketEpoll&& se);

};

};

#endif
