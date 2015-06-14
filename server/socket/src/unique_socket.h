#ifndef UNIQUE_SOCKET_H
#define UNIQUE_SOCKET_H
#include "socket_ns.h"
#include "socket_addr.h"
namespace socket_ns {

class UniqueSocket {
private:
    int m_domain; //address family,socket_ns::af_inet as default
    int m_type; //socket type, socket_ns::sock_stream as default
    int m_protocol; //protocol num, 0 as default 
    int m_socket_fd; //socket file descriptor
	bool m_block;
    SocketAddr m_peer_addr; //the remote connected address
    SocketAddr m_sock_addr; //the socket’s own address
private:
    void getsockaddr();
    void getpeeraddr();
public:
    UniqueSocket();
    UniqueSocket(int domain, int type, int protocol);
    UniqueSocket(int domain, int type);
    UniqueSocket(int socket_fd);

	UniqueSocket(const UniqueSocket& s) = delete;
	UniqueSocket(UniqueSocket&& s);
	UniqueSocket& operator=(const UniqueSocket& s) = delete;
	UniqueSocket& operator=(UniqueSocket&& s);

    int bind(const char* ip, unsigned short int port);
    int bind(const string& ip, unsigned short int port);
    int bind(string&& ip, unsigned short int port);
    int bind(const string& ip);
    int bind(string&& ip);
    int bind(const char* ip);
    int connect(const char* ip, unsigned short int port);
    int connect(const string& ip, unsigned short int port);
    int connect(string&& ip, unsigned short int port);
    int listen(int backlog);
    int listen();
    UniqueSocket accept();
	int setblocking(bool block);
	bool block();
    int send(const string& data) const;
    int send(string&& data) const;
    int recv(string& data) const;
	int get_fd() const;
    Address getsockname() const;
    Address getpeername() const;
    int close();
    ~UniqueSocket();
};

};

namespace socket_ns {

ostream& operator<< (ostream& os, const UniqueSocket& s);
ostream& operator<< (ostream& os, UniqueSocket&& s);

};
#endif //UNIQUE_SOCKET_H
