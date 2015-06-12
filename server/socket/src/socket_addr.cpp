#include "socket_addr.h"
namespace socket_ns {

SocketAddr::SocketAddr() {
}
SocketAddr::SocketAddr(int domain, string ip, unsigned short int port):
    m_domain(domain),
    m_ip(ip),
    m_port(port){
    ::memset((&m_addr), 0, sizeof(m_addr));
    m_addr.sin_family = af_inet;
    m_addr.sin_port = ::htons(port);
    m_addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    m_size = sizeof(m_addr);
    m_sockaddr_ptr = (struct sockaddr *)&(m_addr);
}
SocketAddr::SocketAddr(struct sockaddr_in addr):m_addr(addr){
    m_size = sizeof(m_addr);
    m_domain = addr.sin_family;
    m_ip = string(::inet_ntoa(addr.sin_addr));
    m_port = ::ntohs(addr.sin_port);
    m_sockaddr_ptr = (struct sockaddr *)&(m_addr);
}
struct sockaddr* SocketAddr::get_sockaddr_ptr() const{
    return m_sockaddr_ptr;
}
unsigned int SocketAddr::get_sockaddr_size() const {
    return m_size;
}

Address SocketAddr::get_address() const {
    return Address(m_ip, m_port);
}

};
