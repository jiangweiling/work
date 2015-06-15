#include "socket.h"
namespace socket_ns {

Socket::Socket(shared_ptr<UniqueSocket> socket_ptr):
	m_socket_ptr(socket_ptr) {  
	//m_socket_ptr(new UniqueSocket()) {  
	//cerr<<"Socket()\n";
	//cerr<<"Socket()exit\n";
}

Socket::Socket(int domain, int type, int protocol):
	m_socket_ptr(new UniqueSocket(domain, type, protocol)) {
	//cerr<<"Socket(int,int,int)\n";
	//cerr<<"Socket(int,int,int)exit\n";
}

Socket::Socket(int socket_fd):
	m_socket_ptr(UniqueSocket::make_shared(socket_fd)){
	//cerr<<"Socket(int)\n";
	//cerr<<"Socket(int)exit\n";
}


Socket::Socket(const Socket& s):
	m_socket_ptr(s.m_socket_ptr){
	//cerr<<"Socket(const Socket&)\n";
	//cerr<<"Socket(const Socket&)exit\n";
}

Socket::Socket(Socket&& s):
	m_socket_ptr(move(s.m_socket_ptr)){
	//cerr<<"Socket(Socket&&)\n";
	//cerr<<"Socket(Socket&&)exit\n";
}

Socket& Socket::operator= (const Socket& s) {
	//cerr<<"operator=(const Socket&)\n";
	m_socket_ptr = s.m_socket_ptr;
	//cerr<<"operator=(const Socket&)exit\n";
	return *this;
}
Socket& Socket::operator= (Socket&& s) {
	//cerr<<"operator=(Socket&&)\n";
	m_socket_ptr = move(s.m_socket_ptr);
	//cerr<<"operator=(Socket&&)exit\n";
	return *this;
}

};



namespace socket_ns {

int Socket::bind(const char* ip, unsigned short int port) {
	//cerr<<"int Socket::bind(const char* ip, unsigned short int port)\n";
	int ret = m_socket_ptr->bind(ip, port);
	//cerr<<"int Socket::bind(const char* ip, unsigned short int port)exit\n";
	return ret;
}

int Socket::bind(const string& ip, unsigned short int port) {
	//cerr<<"int Socket::bind(const string& ip, unsigned short int port)\n";
	int ret = m_socket_ptr->bind(ip.c_str(), port);
	//cerr<<"int Socket::bind(const string& ip, unsigned short int port)exit\n";
    return ret;
}

int Socket::bind(string&& ip, unsigned short int port) {
	//cerr<<"int Socket::bind(string&& ip, unsigned short int port)\n";
	int ret = m_socket_ptr->bind(ip.c_str(), port);
	//cerr<<"int Socket::bind(string&& ip, unsigned short int port)exit\n";
    return ret;
}

int Socket::connect(const char* ip, unsigned short int port) {
	//cerr<<"int Socket::connect(const char* ip, unsigned short int port)\n";
	int ret = m_socket_ptr->connect(ip, port);
	//cerr<<"int Socket::connect(const char* ip, unsigned short int port)exit\n";
	return ret;
}

int Socket::connect(const string& ip, unsigned short int port) {
	//cerr<<"int Socket::connect(const string& ip, unsigned short int port)\n";
	int ret = m_socket_ptr->connect(ip.c_str(), port);
	//cerr<<"int Socket::connect(const string& ip, unsigned short int port)exit\n";
    return ret;
}

int Socket::connect(string&& ip, unsigned short int port) {
	//cerr<<"int Socket::connect(string&& ip, unsigned short int port)\n";
	int ret = m_socket_ptr->connect(ip.c_str(), port);
	//cerr<<"int Socket::connect(string&& ip, unsigned short int port)exit\n";
    return ret;
}

int Socket::listen(int backlog) {
	//cerr<<"int Socket::listen(int backlog)\n";
	int ret = m_socket_ptr->listen(backlog);
	//cerr<<"int Socket::listen(int backlog)exit\n";
    return ret;
}


Socket Socket::accept() {
	//cerr<<"Socket Socket::accept()\n";
	Socket s(m_socket_ptr->accept());
	//cerr<<"Socket Socket::accept()exit\n";
    return move(s);
}

int Socket::get_fd() const {
	//cerr<<"int Socket::get_fd() const\n";
	int m_socket_fd = m_socket_ptr->get_fd();
	//cerr<<"int Socket::get_fd() const exit\n";
	return m_socket_fd;
}

Address Socket::getsockname() const {
	//cerr<<"Address Socket::getsockname() const\n";
	Address addr(m_socket_ptr->getsockname());
	//cerr<<"Address Socket::getsockname() const exit\n";
    return move(addr);
}
Address Socket::getpeername() const {
	//cerr<<"Address Socket::getpeername() const\n";
	Address addr(m_socket_ptr->getpeername());
	//cerr<<"Address Socket::getpeername() const exit\n";
    return move(addr);
}
int Socket::send(const char* data) const{
	//cerr<<"int Socket::send(const char* data) const \n";
	int ret = m_socket_ptr->send(data);
	//cerr<<"int Socket::send(const char* data) const exit\n";
    return ret;
}

int Socket::send(const string& data) const{
	//cerr<<"int Socket::send(const string& data) const \n";
	int ret = m_socket_ptr->send(data.c_str());
	//cerr<<"int Socket::send(const string& data) const exit\n";
    return ret;
}
int Socket::send(string&& data) const{
	//cerr<<"int Socket::send(string&& data) const \n";
	int ret = m_socket_ptr->send(data.c_str());
	//cerr<<"int Socket::send(string&& data) const exit\n";
	return ret;
}

bool Socket::recv(string& data) const {
	//cerr<<"int Socket::recv(string& data) const\n";
	auto ret = m_socket_ptr->recv(data);
	//cerr<<"int Socket::recv(string& data) const exit\n";
    return ret;
}

int Socket::setblocking(bool block) {
	//cerr<<"int Socket::setblocking(bool block)\n";
	int ret = m_socket_ptr->setblocking(block);
	//cerr<<"int Socket::setblocking(bool block) exit\n";
	return ret;
}

bool Socket::block() {
	//cerr<<"bool Socket::block()\n";
	bool ret = m_socket_ptr->block();
	//cerr<<"bool Socket::block()exit\n";
	return ret;
}

shared_ptr<UniqueSocket> Socket::get_socket_ptr() const{
	return m_socket_ptr;
}
};

namespace socket_ns {

ostream& operator<< (ostream& os, const Socket& s) {
	os<<*(s.get_socket_ptr());
	return os;
}

ostream& operator<< (ostream& os, Socket&& s) {
	os<<*(s.get_socket_ptr());
	return os;
}

};


namespace socket_ns {

/*
Socket::Socket(int domain, int type):
	m_socket_ptr(new UniqueSocket(domain, type)) {
	cerr<<"Socket(int,int)\n";
	cerr<<"Socket(int,int)exit\n";
}
*/

/*
int Socket::bind(const string& ip) {
	cerr<<"int Socket::bind(const string& ip)\n";
	int ret = m_socket_ptr->bind(ip);
	cerr<<"int Socket::bind(const string& ip)exit\n";
    return ret;
}
int Socket::bind(string&& ip) {
	cerr<<"int Socket::bind(string&& ip)\n";
	int ret = m_socket_ptr->bind(ip);
	cerr<<"int Socket::bind(string&& ip)exit\n";
    return ret;
}

int Socket::bind(const char* ip) {
	cerr<<"int Socket::bind(const char* ip)\n";
	int ret = m_socket_ptr->bind(ip);
	cerr<<"int Socket::bind(const char* ip)exit\n";
	return ret;
}
*/

/*
int Socket::listen() {
	cerr<<"int Socket::listen(int)\n";
	int ret = m_socket_ptr->listen();
	cerr<<"int Socket::listen(int)exit\n";
	return ret;
}
*/
};
