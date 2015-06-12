#ifndef SOCKET_H
#define SOCKET_H
#include "socket_ns.h"
#include "socket_addr.h"
namespace socket_ns {

class Socket {
private:
    int m_domain; //address family,socket_ns::af_inet as default
    int m_type; //socket type, socket_ns::sock_stream as default
    int m_protocol; //protocol num, 0 as default 
    int m_socket_fd; //socket file descriptor
    SocketAddr m_peer_addr; //the remote connected address
    SocketAddr m_sock_addr; //the socket’s own address
    void getsockaddr();
public:
    Socket(int domain, int type, int protocol);
    Socket(int domain, int type);
    Socket(int socket_fd);
    Socket();
    ~Socket();
    int bind(const string& ip, unsigned short int port);
    int bind(const char* ip, unsigned short int port);
    int bind(const string& ip);
    int bind(const char* ip);
    int connect(const string& ip, unsigned short int port);
    int connect(const char* ip, unsigned short int port);
    int listen(int backlog);
    pair<Socket, Address> accept();
    int send(const string& data);
    int recv(string& data);
    int close();
    Address getsockname() const;
    Address getpeername() const;
};

};
#endif //SOCKET_H
