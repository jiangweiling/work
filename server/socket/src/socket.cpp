#include "socket.h"
namespace socket_ns {


Socket::Socket():
	m_socket_ptr(UniqueSocket::make_shared()) {
}

Socket::Socket(shared_ptr<UniqueSocket> socket_ptr):
	m_socket_ptr(socket_ptr) {  
}

Socket::Socket(int domain, int type, int protocol):
	m_socket_ptr(UniqueSocket::make_shared(domain, type, protocol)) {
}

Socket::Socket(int socket_fd):
	m_socket_ptr(UniqueSocket::make_shared(socket_fd)){
}

Socket::Socket(const Socket& s)=default;

Socket::Socket(Socket&& s):
	m_socket_ptr(move(s.m_socket_ptr)){
}

Socket& Socket::operator= (const Socket& s)=default;

Socket& Socket::operator= (Socket&& s) {
	m_socket_ptr = move(s.m_socket_ptr);
	return *this;
}

Socket::~Socket(){
}
};



namespace socket_ns {

int Socket::bind(const char* ip, unsigned short int port) {
	return m_socket_ptr->bind(ip, port);
}

int Socket::bind(const string& ip, unsigned short int port) {
	return m_socket_ptr->bind(ip.c_str(), port);
}

int Socket::bind(string&& ip, unsigned short int port) {
	return m_socket_ptr->bind(ip.c_str(), port);
}

int Socket::connect(const char* ip, unsigned short int port) {
	return m_socket_ptr->connect(ip, port);
}

int Socket::connect(const string& ip, unsigned short int port) {
	return m_socket_ptr->connect(ip.c_str(), port);
}

int Socket::connect(string&& ip, unsigned short int port) {
	return m_socket_ptr->connect(ip.c_str(), port);
}

int Socket::listen(int backlog) {
	return m_socket_ptr->listen(backlog);
}


Socket Socket::accept() {
	return Socket(m_socket_ptr->accept());
}

int Socket::setblocking(bool block) {
	return m_socket_ptr->setblocking(block);
}

bool Socket::block() {
	return m_socket_ptr->block();
}

void Socket::close() {
	UniqueSocket::rm_usocket(m_socket_ptr->get_fd());
	m_socket_ptr = nullptr;
}
int Socket::get_fd() const {
	return m_socket_ptr->get_fd();
}

int Socket::send(const char* data) const{
	return m_socket_ptr->send(data);
}

int Socket::send(const string& data) const{
	return m_socket_ptr->send(data.c_str());
}
int Socket::send(string&& data) const{
	return m_socket_ptr->send(data.c_str());
}

bool Socket::recv(string& data) const {
	return m_socket_ptr->recv(data);
}

Address Socket::getsockname() const {
	return Address(m_socket_ptr->getsockname());
}
Address Socket::getpeername() const {
	return Address(m_socket_ptr->getpeername());
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

