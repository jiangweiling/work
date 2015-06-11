#ifndef SOCKET_H
#define SOCKET_H
#include "socket_ns.h"
#include "socket_addr.h"
namespace socket_ns {

class Socket {
private:
    int m_domain;
    int m_type;
    int m_protocol;
    int m_socket_fd;
    SocketAddr m_peer_addr;
    SocketAddr m_sock_addr;
    void getsockaddr();
public:
    Socket(int domain, int type, int protocol);
    Socket(int domain, int type);
    Socket(int socket_fd);
    Socket();
    ~Socket();
    int bind(string ip, unsigned short int port);
    int bind(string ip);
    int connect(string ip, unsigned short int port);
    int listen(int backlog);
    pair<Socket, Address> accept();
    int send(string data);
    int recv(string& data);
    int close();
    Address getsockname() const;
    Address getpeername() const;
};
};
#endif //SOCKET_H
