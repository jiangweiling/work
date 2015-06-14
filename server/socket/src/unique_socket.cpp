#include "unique_socket.h"
namespace socket_ns {

UniqueSocket::UniqueSocket():
    m_domain(af_inet),      //socket_ns::af_inet 
    m_type(sock_stream),    //socket_ns::sock_stream
    m_protocol(0),          
    m_socket_fd(::socket(m_domain, m_type, m_protocol)), // sys/socket.h
	m_block(true){  
	cerr<<"UniqueSocket()\n";
	cerr<<"UniqueSocket()exit\n";
}

UniqueSocket::UniqueSocket(int domain, int type, int protocol):
    m_domain(domain), 
    m_type(type), 
    m_protocol(protocol), 
    m_socket_fd(::socket(domain, type, protocol)),  // sys/socket.h
	m_block(true) {
	cerr<<"UniqueSocket(int,int,int)\n";
	cerr<<"UniqueSocket(int,int,int)exit\n";
}

UniqueSocket::UniqueSocket(int domain, int type):
    m_domain(domain), 
    m_type(type), 
    m_protocol(0), 
    m_socket_fd(::socket(domain, type, 0)),  // sys/socket.h
	m_block(true) {
	cerr<<"UniqueSocket(int,int)\n";
	cerr<<"UniqueSocket(int,int)exit\n";
}

UniqueSocket::UniqueSocket(int socket_fd):
	m_domain(af_inet),   // socket_ns::af_inet
	m_type(sock_stream), // socket_ns::sock_stream
	m_protocol(0),
	m_socket_fd(socket_fd){
	cerr<<"UniqueSocket(int)\n";
	m_block = block();
	getsockaddr();
	getpeeraddr();
	cerr<<"UniqueSocket(int)exit\n";
}


UniqueSocket::UniqueSocket(UniqueSocket&& s):
	m_domain(s.m_domain),
	m_type(s.m_type),
	m_protocol(s.m_protocol),
	m_socket_fd(s.m_socket_fd),
	m_block(s.m_block),
	m_peer_addr(move(s.m_peer_addr)),
	m_sock_addr(move(s.m_sock_addr)) {
	s.m_socket_fd = -1;
	cerr<<"UniqueSocket(const UniqueSocket&)\n";
}

UniqueSocket& UniqueSocket::operator= (UniqueSocket&& s) {
	cerr<<"operator=(UniqueSocket&&)\n";
	m_domain = s.m_domain;
	m_type = s.m_type;
	m_protocol = s.m_protocol;
	m_socket_fd = s.m_socket_fd;
	s.m_socket_fd = -1;
	m_block = s.m_block;
	m_peer_addr = move(s.m_peer_addr);
	m_sock_addr = move(s.m_sock_addr);
	cerr<<"operator=(UniqueSocket&&)end\n";
	return *this;
}

};



namespace socket_ns {

int UniqueSocket::bind(const char* ip, unsigned short int port) {
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

int UniqueSocket::bind(const string& ip, unsigned short int port) {
	cerr<<"bind(const string&, unsigned short)\n";
    return bind(ip.c_str(), port);
}

int UniqueSocket::bind(string&& ip, unsigned short int port) {
	cerr<<"bind(string&&, unsigned short)\n";
    return bind(ip.c_str(), port);
}

int UniqueSocket::bind(const string& ip) {
	cerr<<"bind(const string&)\n";
    return bind(ip.c_str(), 0);
}

int UniqueSocket::bind(string&& ip) {
	cerr<<"bind(string&&)\n";
    return bind(ip.c_str(), 0);
}

int UniqueSocket::bind(const char* ip) {
	cerr<<"bind(const char*)\n";
	return bind(ip, 0);
}

int UniqueSocket::connect(const char* ip, unsigned short int port) {
    m_peer_addr = SocketAddr(m_domain, ip, port);
    int ret = ::connect(m_socket_fd, 
			m_peer_addr.get_sockaddr_ptr(), 
			m_peer_addr.get_sockaddr_size()); // sys/socket.h
    getsockaddr();
	cerr<<"connect(const char*, unsigned short)\n";
	return ret;
}

int UniqueSocket::connect(const string& ip, unsigned short int port) {
	cerr<<"connect(const string&, unsigned short)\n";
    return connect(ip.c_str(), port);
}

int UniqueSocket::connect(string&& ip, unsigned short int port) {
	cerr<<"connect(string&&, unsigned short)\n";
    return connect(ip.c_str(), port);
}

int UniqueSocket::listen(int backlog) {
	cerr<<"listen(int)\n";
    return ::listen(m_socket_fd, backlog); // sys/socket.h
}

int UniqueSocket::listen() {
	cerr<<"listen()\n";
    return ::listen(m_socket_fd, 10); // sys/socket.h
}

UniqueSocket UniqueSocket::accept() {
	cerr<<"accept()\n";
    struct sockaddr_in addr; // netinet/in.h
    unsigned int size;
    int socket_fd = ::accept(m_socket_fd, (struct sockaddr *)&addr, &size); // sys/socket.h
    if(socket_fd != -1) {
        SocketAddr socket_addr(addr);
        return UniqueSocket(socket_fd);
    }
    return UniqueSocket();
}

int UniqueSocket::get_fd() const {
	return m_socket_fd;
}
void UniqueSocket::getsockaddr() {
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

void UniqueSocket::getpeeraddr() {
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

Address UniqueSocket::getsockname() const {
	cerr<<"getsockname\n";
    return m_sock_addr.get_address();
}
Address UniqueSocket::getpeername() const {
	cerr<<"getpeername\n";
    return m_peer_addr.get_address();
}

int UniqueSocket::send(const string& data) const{
	cerr<<"send(cosnt string&)\n";
    const char* str = data.c_str();
    return ::send(m_socket_fd, str, strlen(str)+1, 0); // sys/socket.h
}
int UniqueSocket::send(string&& data) const{
	cerr<<"send(string&&)\n";
    const char* str = data.c_str();
    return ::send(m_socket_fd, str, strlen(str)+1, 0); // sys/socket.h
}

int UniqueSocket::recv(string& data) const {
	cerr<<"recv(string&)\n";
    char buffer[buf_size];
    int ret = ::recv(m_socket_fd, buffer, buf_size, 0);  // sys/socket.h
    data = string(buffer);
    return ret;
}
UniqueSocket::~UniqueSocket() {
	cerr<<"~UniqueSocket()\n";
    close();
}
int UniqueSocket::close() {
	cerr<<"close\n";
    if (m_socket_fd == -1) {
        return -1;
    }
    return ::close(m_socket_fd); // unistd.h
}

int UniqueSocket::setblocking(bool block) {
	int flags;
	flags = fcntl(m_socket_fd, F_GETFL, 0);  // fcntl.h
	if (-1==flags or 0!=errno) {
		cerr<<"UniqueSocket::setblocking error\n";
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
		cerr<<"UniqueSocket::setblocking error\n";
		cerr<<strerror(errno)<<endl;;
		return -1;
	}
	m_block = block;
	return 0;
}

bool UniqueSocket::block() {
	int flags = fcntl(m_socket_fd, F_GETFL, 0);  // fcntl.h
	if (-1==flags or 0!=errno) {
		cerr<<"UniqueSocket::block error\n";
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

ostream& operator<< (ostream& os, const UniqueSocket& s) {
	os<<"< socket_fd = "<<s.get_fd()
		<<", sockname = "<<s.getsockname()
		<<", peername = "<<s.getpeername()
		<<" >";
	return os;
}

ostream& operator<< (ostream& os, UniqueSocket&& s) {
	os<<"< socket_fd = "<<s.get_fd()
		<<", sockname = "<<s.getsockname()
		<<", peername = "<<s.getpeername()
		<<" >";
	return os;
}

};

namespace socket_ns {
/*
UniqueSocket::UniqueSocket(const UniqueSocket& s):
	m_domain(s.m_domain),
	m_type(s.m_type),
	m_protocol(s.m_protocol),
	m_socket_fd(s.m_socket_fd),
	m_block(s.m_block),
	m_peer_addr(s.m_peer_addr),
	m_sock_addr(s.m_sock_addr){
	cerr<<"UniqueSocket(const UniqueSocket&)\n";
	cerr<<"UniqueSocket(const UniqueSocket&)exit\n";
}
*/
/*
UniqueSocket& UniqueSocket::operator= (const UniqueSocket& s) {
	cerr<<"operator=(const UniqueSocket&)\n";
	m_domain = s.m_domain;
	m_type = s.m_type;
	m_protocol = s.m_protocol;
	m_socket_fd = s.m_socket_fd;
	m_block = s.m_block;
	m_peer_addr = s.m_peer_addr;
	m_sock_addr = s.m_sock_addr;
	return *this;
}
*/

};
