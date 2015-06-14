#include "socket_epoll.h"
namespace socket_ns {

const int SocketEpoll::socket_event = EPOLLIN|EPOLLET ;   // 用于检测socket是否可读, sys/epoll.h 
const int SocketEpoll::socket_readable = EPOLLIN ;   // 用于检测socket是否可读, sys/epoll.h 

SocketEpoll::SocketEpoll(int size):
	m_size(size),
	m_epfd(epoll_create(m_size)),
	m_event_ptr(new epoll_event_t[m_size]){
	cerr<<"SocketEpoll::SocketEpoll(int size)\n";
	if(errno) {
		cerr<<strerror(errno)<<endl;
	}
	cerr<<"SocketEpoll::SocketEpoll(int size)exit\n";
}

SocketEpoll::SocketEpoll(SocketEpoll&& se):
	m_size(se.m_size),
	m_epfd(se.m_epfd),
	m_event_ptr(se.m_event_ptr){
	cerr<<"SocketEpoll::SocketEpoll(SocketEpoll&& se)\n";
	if(errno) {
		cerr<<strerror(errno)<<endl;
	}
	se.m_epfd = -1;
	se.m_event_ptr = nullptr;
	cerr<<"SocketEpoll::SocketEpoll(SocketEpoll&& se)exit\n";
}


SocketEpoll& SocketEpoll::operator= (SocketEpoll&& se){
	cerr<<"SocketEpoll& SocketEpoll::operator= (SocketEpoll&& se)\n";
	m_size = se.m_size;
	m_epfd = se.m_epfd;
	m_event_ptr = se.m_event_ptr;
	se.m_epfd = -1;
	se.m_event_ptr = nullptr;
	cerr<<"SocketEpoll& SocketEpoll::operator= (SocketEpoll&& se)exit\n";
	return *this;
}

SocketEpoll::~SocketEpoll() {
	cerr<<"SocketEpoll::~SocketEpoll()\n";
	m_epfd = -1;
	delete[] m_event_ptr;
	m_event_ptr = nullptr;
	cerr<<"SocketEpoll::~SocketEpoll()exit\n";
}

int SocketEpoll::add(const Socket& s) {
	cerr<<"int SocketEpoll::add(const Socket& s)\n";
	epoll_event_t e;
	e.data.fd = s.get_fd();
	e.events = socket_event; // static const int SocektEpoll::socket_event
	int ret = epoll_ctl(m_epfd, EPOLL_CTL_ADD, e.data.fd, &e); // sys/epoll.h
	if(errno) {
		cerr<<strerror(errno)<<endl;
	}
	cerr<<"int SocketEpoll::add(const Socket& s)exit\n";
	return ret;
}
int SocketEpoll::remove(const Socket& s) {
	cerr<<"int SocketEpoll::remove(const Socket& s)\n";
	epoll_event_t e;
	e.data.fd = s.get_fd();
	e.events = socket_event; // static const int SocektEpoll::socket_event
	int ret = epoll_ctl(m_epfd, EPOLL_CTL_DEL, e.data.fd, &e); // sys/epoll.h
	if(errno) {
		cerr<<strerror(errno)<<endl;
	}
	cerr<<"int SocketEpoll::remove(const Socket& s)exit\n";
	return ret;
}

int SocketEpoll::wait(int timeout) {
	cerr<<"int SocketEpoll::wait(int timeout)\n";
	int n = epoll_wait(m_epfd, m_event_ptr, m_size, timeout); // sys/epoll.h
	if(errno) {
		cerr<<strerror(errno)<<endl;
	}
	cerr<<"int SocketEpoll::wait(int timeout)exit\n";
	return n;
}

};
