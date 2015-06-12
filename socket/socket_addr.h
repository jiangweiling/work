#ifndef SOCKET_ADDR_H
#define SOCKET_ADDR_H
#include "socket_ns.h"
namespace socket_ns {

class SocketAddr {
private:
    struct sockaddr_in m_addr;
    struct sockaddr *m_sockaddr_ptr;
    unsigned int m_size;
    int m_domain;
    string m_ip;
    unsigned short int m_port;
public:
    SocketAddr();
    SocketAddr(const SocketAddr& sa);
    SocketAddr& operator= (const SocketAddr& sa);
    SocketAddr(int domain, const string& ip, unsigned short int port);
    SocketAddr(struct sockaddr_in addr);
    struct sockaddr *get_sockaddr_ptr() const;
    unsigned int get_sockaddr_size() const;
    Address get_address() const;
};

};
#endif //SOCKET_ADDR_H
