#ifndef SOCKET_ADDR_H
#define SOCKET_ADDR_H
#include "socket_ns.h"

namespace socket_ns {

class SocketAddr {
private:
    struct sockaddr_in m_addr;
    unsigned int m_size;
    int m_domain;
    string m_ip;
    unsigned short int m_port;
private:
	void m_addr_ctor(int domain, const char* ip, unsigned short int port);
public:
	SocketAddr();
    SocketAddr(int domain, const string& ip, unsigned short int port);
    SocketAddr(int domain, const char* ip, unsigned short int port);
    SocketAddr(int domain, string&& ip, unsigned short int port);
    SocketAddr(const string& ip, unsigned short int port);
    SocketAddr(const char* ip, unsigned short int port);
    SocketAddr(string&& ip, unsigned short int port);
    SocketAddr(struct sockaddr_in addr);
    SocketAddr(const SocketAddr& sa);
    SocketAddr(SocketAddr&& sa);

    SocketAddr& operator= (const SocketAddr& sa);
    SocketAddr& operator= (SocketAddr&& sa);

    struct sockaddr *get_sockaddr_ptr() const;
    unsigned int get_sockaddr_size() const;
    Address get_address() const;
};

};

namespace socket_ns {

ostream& operator<< (ostream& os, const Address& addr);
ostream& operator<< (ostream& os, Address&& addr);

ostream& operator<< (ostream& os, const SocketAddr& sa);
ostream& operator<< (ostream& os, SocketAddr&& sa);

};
#endif //SOCKET_ADDR_H
