#include "socket.h"
namespace socket_ns {

Socket::Socket():
    m_domain(af_inet),      //socket_ns::af_inet 
    m_type(sock_stream),    //socket_ns::sock_stream
    m_protocol(0),          
    m_socket_fd(::socket(m_domain, m_type, m_protocol)), // sys/socket.h
	m_block(true){  
	cerr<<"Socket()\n";
	socket_ptr = shared_ptr<UniqueSocket>new UniqueSocket()
	cerr<<"Socket()exit\n";
}

Socket::Socket(int domain, int type, int protocol):
    m_domain(domain), 
    m_type(type), 
    m_protocol(protocol), 
    m_socket_fd(::socket(domain, type, protocol)),  // sys/socket.h
	m_block(true) {
	cerr<<"Socket(int,int,int)\n";
	cerr<<"Socket(int,int,int)exit\n";
}

Socket::Socket(int domain, int type):
    m_domain(domain), 
    m_type(type), 
    m_protocol(0), 
    m_socket_fd(::socket(domain, type, 0)),  // sys/socket.h
	m_block(true) {
	cerr<<"Socket(int,int)\n";
	cerr<<"Socket(int,int)exit\n";
}

Socket::Socket(int socket_fd):
	m_domain(af_inet),   // socket_ns::af_inet
	m_type(sock_stream), // socket_ns::sock_stream
	m_protocol(0),
	m_socket_fd(socket_fd){
	cerr<<"Socket(int)\n";
	m_block = block();
	getsockaddr();
	getpeeraddr();
	cerr<<"Socket(int)exit\n";
}


Socket::Socket(Socket&& s):
	m_domain(s.m_domain),
	m_type(s.m_type),
	m_protocol(s.m_protocol),
	m_socket_fd(s.m_socket_fd),
	m_block(s.m_block),
	m_peer_addr(move(s.m_peer_addr)),
	m_sock_addr(move(s.m_sock_addr)) {
	s.m_socket_fd = -1;
	cerr<<"Socket(const Socket&)\n";
}

Socket& Socket::operator= (Socket&& s) {
	cerr<<"operator=(Socket&&)\n";
	m_domain = s.m_domain;
	m_type = s.m_type;
	m_protocol = s.m_protocol;
	m_socket_fd = s.m_socket_fd;
	s.m_socket_fd = -1;
	m_block = s.m_block;
	m_peer_addr = move(s.m_peer_addr);
	m_sock_addr = move(s.m_sock_addr);
	cerr<<"operator=(Socket&&)end\n";
	return *this;
}

};



namespace socket_ns {

int Socket::bind(const char* ip, unsigned short int port) {
	cerr<<"bind(const char*, unsigned short)\n";
	cerr<<"ip: "<<ip<<" port: "<<port<<'\n';
    SocketAddr addr(m_domain, ip, port);
    int ret = ::bind(m_socket_fd,       // sys/socket.h 
			addr.get_sockaddr_ptr(), 
			addr.get_sockaddr_size()); 
    getsockaddr();
	if(0 != ret) {
		cerr<<"bind fail\n";
	}
	return ret;
}

int Socket::bind(const string& ip, unsigned short int port) {
	cerr<<"bind(const string&, unsigned short)\n";
    return bind(ip.c_str(), port);
}

int Socket::bind(string&& ip, unsigned short int port) {
	cerr<<"bind(string&&, unsigned short)\n";
    return bind(ip.c_str(), port);
}

int Socket::bind(const string& ip) {
	cerr<<"bind(const string&)\n";
    return bind(ip.c_str(), 0);
}

int Socket::bind(string&& ip) {
	cerr<<"bind(string&&)\n";
    return bind(ip.c_str(), 0);
}

int Socket::bind(const char* ip) {
	cerr<<"bind(const char*)\n";
	return bind(ip, 0);
}

int Socket::connect(const char* ip, unsigned short int port) {
    m_peer_addr = SocketAddr(m_domain, ip, port);
    int ret = ::connect(m_socket_fd, 
			m_peer_addr.get_sockaddr_ptr(), 
			m_peer_addr.get_sockaddr_size()); // sys/socket.h
    getsockaddr();
	cerr<<"connect(const char*, unsigned short)\n";
	return ret;
}

int Socket::connect(const string& ip, unsigned short int port) {
	cerr<<"connect(const string&, unsigned short)\n";
    return connect(ip.c_str(), port);
}

int Socket::connect(string&& ip, unsigned short int port) {
	cerr<<"connect(string&&, unsigned short)\n";
    return connect(ip.c_str(), port);
}

int Socket::listen(int backlog) {
	cerr<<"listen(int)\n";
    return ::listen(m_socket_fd, backlog); // sys/socket.h
}

int Socket::listen() {
	cerr<<"listen()\n";
    return ::listen(m_socket_fd, 10); // sys/socket.h
}

Socket Socket::accept() {
	cerr<<"accept()\n";
    struct sockaddr_in addr; // netinet/in.h
    unsigned int size;
    int socket_fd = ::accept(m_socket_fd, (struct sockaddr *)&addr, &size); // sys/socket.h
    if(socket_fd != -1) {
        SocketAddr socket_addr(addr);
        return Socket(socket_fd);
    }
    return Socket();
}

int Socket::get_fd() const {
	return m_socket_fd;
}
void Socket::getsockaddr() {
	cerr<<"getsockaddr()\n";
    struct sockaddr_in addr; // netinet/in.h
    unsigned int size = sizeof(addr);
    ::memset(&addr, 0, size); // cstring
    int ret = ::getsockname(m_socket_fd, (struct sockaddr *)&addr, &size);
    if(ret == 0) {
        m_sock_addr = SocketAddr(addr);
    }
    else{
        m_sock_addr = SocketAddr(m_domain, string(""), 0);
    }
}

void Socket::getpeeraddr() {
	cerr<<"getpeeraddr()\n";
    struct sockaddr_in addr; // netinet/in.h
    unsigned int size = sizeof(addr);
    ::memset(&addr, 0, size); // cstring
    int ret = ::getpeername(m_socket_fd, (struct sockaddr *)&addr, &size);
    if(ret == 0) {
        m_peer_addr = SocketAddr(addr);
    }
    else{
        m_peer_addr = SocketAddr(m_domain, string(""), 0);
    }
}

Address Socket::getsockname() const {
	cerr<<"getsockname\n";
    return m_sock_addr.get_address();
}
Address Socket::getpeername() const {
	cerr<<"getpeername\n";
    return m_peer_addr.get_address();
}

int Socket::send(const string& data) const{
	cerr<<"send(cosnt string&)\n";
    const char* str = data.c_str();
    return ::send(m_socket_fd, str, strlen(str)+1, 0); // sys/socket.h
}
int Socket::send(string&& data) const{
	cerr<<"send(string&&)\n";
    const char* str = data.c_str();
    return ::send(m_socket_fd, str, strlen(str)+1, 0); // sys/socket.h
}

int Socket::recv(string& data) const {
	cerr<<"recv(string&)\n";
    char buffer[buf_size];
    int ret = ::recv(m_socket_fd, buffer, buf_size, 0);  // sys/socket.h
    data = string(buffer);
    return ret;
}
Socket::~Socket() {
	cerr<<"~Socket()\n";
    close();
}
int Socket::close() {
	cerr<<"close\n";
    if (m_socket_fd == -1) {
        return -1;
    }
    return ::close(m_socket_fd); // unistd.h
}

int Socket::setblocking(bool block) {
	int flags;
	flags = fcntl(m_socket_fd, F_GETFL, 0);  // fcntl.h
	if (-1==flags or 0!=errno) {
		cerr<<"Socket::setblocking error\n";
		cerr<<strerror(errno)<<endl;;
		return -1;
	}
	if(block){ //set block
		flags &= (~O_NONBLOCK);
	}
	else{
		flags |= O_NONBLOCK;
	}
	if (-1 == fcntl(m_socket_fd, F_SETFL, flags) or 0!=errno) {  // fcntl.h
		cerr<<"Socket::setblocking error\n";
		cerr<<strerror(errno)<<endl;;
		return -1;
	}
	m_block = block;
	return 0;
}

bool Socket::block() {
	int flags = fcntl(m_socket_fd, F_GETFL, 0);  // fcntl.h
	if (-1==flags or 0!=errno) {
		cerr<<"Socket::block error\n";
		cerr<<strerror(errno)<<endl;;
		return m_block;
	}
	if( (flags&O_NONBLOCK) == O_NONBLOCK) {
		m_block = false;
	}
	else {
		m_block = true;
	}
	return m_block;
}

};

namespace socket_ns {

ostream& operator<< (ostream& os, const Socket& s) {
	os<<"< socket_fd = "<<s.get_fd()
		<<", sockname = "<<s.getsockname()
		<<", peername = "<<s.getpeername()
		<<" >";
	return os;
}

ostream& operator<< (ostream& os, Socket&& s) {
	os<<"< socket_fd = "<<s.get_fd()
		<<", sockname = "<<s.getsockname()
		<<", peername = "<<s.getpeername()
		<<" >";
	return os;
}

};

