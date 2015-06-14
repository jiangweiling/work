#include "unique_socket.h"
namespace socket_ns {

UniqueSocket::UniqueSocket():
    m_domain(af_inet),      //socket_ns::af_inet 
    m_type(sock_stream),    //socket_ns::sock_stream
    m_protocol(0),          
    m_socket_fd(::socket(m_domain, m_type, m_protocol)), // sys/socket.h
	m_block(true){  
	cerr<<"UniqueSocket::UniqueSocket()\n";
	if(0!=errno) {
		cerr<<strerror(errno);
	}
	cerr<<"UniqueSocket::UniqueSocket()exit\n";
}

UniqueSocket::UniqueSocket(int domain, int type, int protocol):
    m_domain(domain), 
    m_type(type), 
    m_protocol(protocol), 
    m_socket_fd(::socket(domain, type, protocol)),  // sys/socket.h
	m_block(true) {
	cerr<<"UniqueSocket::UniqueSocket(int domain, int type, int protocol)\n";
	if(0!=errno) {
		cerr<<strerror(errno);
	}
	cerr<<"UniqueSocket::UniqueSocket(int domain, int type, int protocol)exit\n";
}

UniqueSocket::UniqueSocket(int socket_fd):
	m_domain(af_inet),   // socket_ns::af_inet
	m_type(sock_stream), // socket_ns::sock_stream
	m_protocol(0),
	m_socket_fd(socket_fd){
	cerr<<"UniqueSocket::UniqueSocket(int socket_fd)\n";
	m_block = block();
	getsockaddr();
	getpeeraddr();
	if(0!=errno) {
		cerr<<strerror(errno);
	}
	cerr<<"UniqueSocket::UniqueSocket(int socket_fd)exit\n";
}


UniqueSocket::UniqueSocket(UniqueSocket&& s):
	m_domain(s.m_domain),
	m_type(s.m_type),
	m_protocol(s.m_protocol),
	m_socket_fd(s.m_socket_fd),
	m_block(s.m_block),
	m_peer_addr(move(s.m_peer_addr)),
	m_sock_addr(move(s.m_sock_addr)) {
	cerr<<"UniqueSocket::UniqueSocket(UniqueSocket&& s)\n";
	s.m_socket_fd = -1;
	if(0!=errno) {
		cerr<<strerror(errno);
	}
	cerr<<"UniqueSocket::UniqueSocket(UniqueSocket&& s)exit\n";
}

UniqueSocket& UniqueSocket::operator= (UniqueSocket&& s) {
	cerr<<"UniqueSocket& UniqueSocket::operator= (UniqueSocket&& s)\n";
	m_domain = s.m_domain;
	m_type = s.m_type;
	m_protocol = s.m_protocol;
	m_socket_fd = s.m_socket_fd;
	m_block = s.m_block;
	m_peer_addr = move(s.m_peer_addr);
	m_sock_addr = move(s.m_sock_addr);
	s.m_socket_fd = -1;
	if(0!=errno) {
		cerr<<strerror(errno);
	}
	cerr<<"UniqueSocket& UniqueSocket::operator= (UniqueSocket&& s)exit\n";
	return *this;
}

};



namespace socket_ns {

int UniqueSocket::bind(const char* ip, unsigned short int port) {
	cerr<<"int UniqueSocket::bind(const char* ip, unsigned short int port)\n";
    SocketAddr addr(m_domain, ip, port);
    int ret = ::bind(m_socket_fd,       // sys/socket.h 
			addr.get_sockaddr_ptr(), 
			addr.get_sockaddr_size()); 
    getsockaddr();
	if(0!=ret || 0!=errno) {
		cerr<<*this<<endl;
		cerr<<strerror(errno)<<endl;
	}
	cerr<<"int UniqueSocket::bind(const char* ip, unsigned short int port)exit\n";
	return ret;
}

int UniqueSocket::bind(const string& ip, unsigned short int port) {
    return bind(ip.c_str(), port);
}

int UniqueSocket::bind(string&& ip, unsigned short int port) {
    return bind(ip.c_str(), port);
}

int UniqueSocket::bind(const string& ip) {
    return bind(ip.c_str(), 0);
}

int UniqueSocket::bind(string&& ip) {
    return bind(ip.c_str(), 0);
}

int UniqueSocket::bind(const char* ip) {
	return bind(ip, 0);
}

int UniqueSocket::connect(const char* ip, unsigned short int port) {
	cerr<<"int UniqueSocket::connect(const char* ip, unsigned short int port)\n";
    m_peer_addr = SocketAddr(m_domain, ip, port);
    int ret = ::connect(m_socket_fd, 
			m_peer_addr.get_sockaddr_ptr(), 
			m_peer_addr.get_sockaddr_size()); // sys/socket.h
    getsockaddr();
	if(0!=ret || 0!=errno) {
		cerr<<m_peer_addr<<endl;
		cerr<<strerror(errno);
	}
	cerr<<"int UniqueSocket::connect(const char* ip, unsigned short int port)exit\n";
	return ret;
}

int UniqueSocket::connect(const string& ip, unsigned short int port) {
    return connect(ip.c_str(), port);
}

int UniqueSocket::connect(string&& ip, unsigned short int port) {
    return connect(ip.c_str(), port);
}

int UniqueSocket::listen(int backlog) {
	cerr<<"int UniqueSocket::listen(int backlog)\n";
	int ret = ::listen(m_socket_fd, backlog); // sys/socket.h
	cerr<<"int UniqueSocket::listen(int backlog)exit\n";
	return ret;
}

int UniqueSocket::listen() {
    return listen(10);
}

int UniqueSocket::accept() {
	cerr<<"int UniqueSocket::accept()\n";
    struct sockaddr_in addr; // netinet/in.h
    unsigned int size = sizeof(addr);
    int socket_fd = ::accept(m_socket_fd, (struct sockaddr *)&addr, &size); // sys/socket.h
    if(-1==socket_fd or 0!=errno) {
		cerr<<strerror(errno)<<endl
			<<"m_socket_fd = "<<m_socket_fd<<endl
			<<"socket_fd = "<<socket_fd<<endl;
    }
	cerr<<"int UniqueSocket::accept()exit\n";
    return socket_fd;
}

int UniqueSocket::get_fd() const {
	return m_socket_fd;
}
void UniqueSocket::getsockaddr() {
	cerr<<"void UniqueSocket::getsockaddr()\n";
    struct sockaddr_in addr; // netinet/in.h
    unsigned int size = sizeof(addr);
    ::memset(&addr, 0, size); // cstring
    int ret = ::getsockname(m_socket_fd, (struct sockaddr *)&addr, &size);
    if(ret == 0) {
        m_sock_addr = SocketAddr(addr);
    }
    else{
		if(0!=errno) {
			cerr<<strerror(errno)<<endl;	
		}
        m_sock_addr = SocketAddr(m_domain, string(""), 0);
    }
	cerr<<"void UniqueSocket::getsockaddr()exit\n";
}

void UniqueSocket::getpeeraddr() {
	cerr<<"void UniqueSocket::getpeeraddr()\n";
    struct sockaddr_in addr; // netinet/in.h
    unsigned int size = sizeof(addr);
    ::memset(&addr, 0, size); // cstring
    int ret = ::getpeername(m_socket_fd, (struct sockaddr *)&addr, &size);
    if(ret == 0) {
        m_peer_addr = SocketAddr(addr);
    }
    else{
		if(0!=errno) {
			cerr<<strerror(errno)<<endl;	
		}
        m_peer_addr = SocketAddr(m_domain, string(""), 0);
    }
	cerr<<"void UniqueSocket::getpeeraddr()exit\n";
}

Address UniqueSocket::getsockname() const {
    return m_sock_addr.get_address();
}
Address UniqueSocket::getpeername() const {
    return m_peer_addr.get_address();
}

int UniqueSocket::send(const char* data) const{
	cerr<<"int UniqueSocket::send(const char* data) const\n";
	int ret = ::send(m_socket_fd, data, strlen(data)+1, 0); // sys/socket.h
	if(0!=errno) {
		cerr<<strerror(errno)<<endl;	
	}
	cerr<<"int UniqueSocket::send(const char* data) const exit\n";
    return ret;
}

int UniqueSocket::send(const string& data) const{
	return send(data.c_str());
}

int UniqueSocket::recv(string& data) const {
	cerr<<"int UniqueSocket::recv(string& data) const\n";
    char buffer[buf_size];
    int ret = ::recv(m_socket_fd, buffer, buf_size, 0);  // sys/socket.h
	if(0!=errno) {
		cerr<<strerror(errno)<<endl;	
	}
    data = string(buffer);
	cerr<<"int UniqueSocket::recv(string& data) const exit\n";
    return ret;
}
UniqueSocket::~UniqueSocket() {
	cerr<<"UniqueSocket::~UniqueSocket()\n";
    close();
	cerr<<"UniqueSocket::~UniqueSocket()exit\n";
}
int UniqueSocket::close() {
	cerr<<"int UniqueSocket::close()\n";
    if (m_socket_fd == -1) {
        return -1;
    }
	int ret = ::close(m_socket_fd); // unistd.h
	if(0!=errno) {
		cerr<<strerror(errno)<<endl;	
	}
	cerr<<"int UniqueSocket::close()exit\n";
	return ret;
}

int UniqueSocket::setblocking(bool block) {
	cerr<<"int UniqueSocket::setblocking(bool block)\n";
	int flags;
	flags = fcntl(m_socket_fd, F_GETFL, 0);  // fcntl.h
	if (-1==flags or 0!=errno) {
		cerr<<"flags = fcntl(m_socket_fd, F_GETFL, 0);\n";
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
		cerr<<"fcntl(m_socket_fd, F_SETFL, flags) or 0!=errno)\n";
		cerr<<strerror(errno)<<endl;;
		return -1;
	}
	m_block = block;
	cerr<<"int UniqueSocket::setblocking(bool block)exit\n";
	return 0;
}

bool UniqueSocket::block() {
	cerr<<"bool UniqueSocket::block()\n";
	int flags = fcntl(m_socket_fd, F_GETFL, 0);  // fcntl.h
	if (-1==flags or 0!=errno) {
		cerr<<strerror(errno)<<endl;;
		return m_block;
	}
	if( (flags&O_NONBLOCK) == O_NONBLOCK) {
		m_block = false;
	}
	else {
		m_block = true;
	}
	cerr<<"bool UniqueSocket::block()exit\n";
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
UniqueSocket::UniqueSocket(int domain, int type):
    m_domain(domain), 
    m_type(type), 
    m_protocol(0), 
    m_socket_fd(::socket(domain, type, 0)),  // sys/socket.h
	m_block(true) {
	cerr<<"UniqueSocket::UniqueSocket(int domain, int type)\n";
	if(0!=errno) {
		cerr<<strerror(errno);
	}
	cerr<<"UniqueSocket::UniqueSocket(int domain, int type)exit\n";
}
*/
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
