#include "socket.h"
namespace socket_ns {

Socket::Socket(int domain, int type, int protocol):
    m_domain(domain), 
    m_type(type), 
    m_protocol(protocol), 
    m_socket_fd(::socket(domain, type, protocol)){
}
Socket::Socket(int domain, int type):
    m_domain(domain), 
    m_type(type), 
    m_protocol(0), 
    m_socket_fd(::socket(domain, type, 0)){
}
Socket::Socket(int socket_fd):m_socket_fd(socket_fd){
}
Socket::Socket():m_socket_fd(-1){
}
int Socket::bind(const string& ip, unsigned short int port) {
    SocketAddr addr(m_domain, ip, port);
    int ret = ::bind(m_socket_fd, addr.get_sockaddr_ptr(), addr.get_sockaddr_size());
    Socket::getsockaddr();
    return ret;
}
int Socket::bind(const char* ip, unsigned short int port) {
	return bind(string(ip), port);
}
int Socket::bind(const string& ip) {
    return Socket::bind(ip, 0);
}
int Socket::bind(const char* ip) {
	return bind(string(ip));
}

int Socket::connect(const string& ip, unsigned short int port) {
    m_peer_addr = SocketAddr(m_domain, ip, port);
    int ret = ::connect(m_socket_fd, m_peer_addr.get_sockaddr_ptr(), m_peer_addr.get_sockaddr_size());
    Socket::getsockaddr();
    return ret;
}
int Socket::connect(const char* ip, unsigned short int port) {
	return connect(string(ip), port);
}

int Socket::listen(int backlog) {
    return ::listen(m_socket_fd, backlog);
}

pair<Socket, Address> Socket::accept() {
    struct sockaddr_in addr;
    unsigned int size;
    int socket_fd = ::accept(m_socket_fd, (struct sockaddr *)&addr, &size);    
    if(socket_fd != -1) {
        SocketAddr socket_addr(addr);
        Socket conn_socket(socket_fd);
        return pair<Socket, Address>(move(conn_socket), socket_addr.get_address());
    }
    return pair<Socket, Address>(Socket(), Address());
}
void Socket::getsockaddr() {
    struct sockaddr_in addr;
    unsigned int size = sizeof(addr);
    ::memset(&addr, 0, size);
    int ret = ::getsockname(m_socket_fd, (struct sockaddr *)&addr, &size);
    if(ret == 0) {
        m_sock_addr = SocketAddr(addr);
    }
    else{
        m_sock_addr = SocketAddr(m_domain, string(""), 0);
    }
}
Address Socket::getsockname() const {
    return m_sock_addr.get_address();
}
Address Socket::getpeername() const {
    return m_peer_addr.get_address();
}
int Socket::send(const string& data) {
    const char* str = data.c_str();
    return ::send(m_socket_fd, str, strlen(str)+1, 0);
}
int Socket::recv(string& data) {
    char buffer[buf_size];
    int ret = ::recv(m_socket_fd, buffer, buf_size, 0);
    data = string(buffer);
    return ret;
}
Socket::~Socket() {
    close();
}
int Socket::close() {
    if (m_socket_fd == -1) {
        return -1;
    }
    return ::close(m_socket_fd);
}

};
