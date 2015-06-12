#include "socket_addr.h"
#include <cstring>
namespace socket_ns {

SocketAddr::SocketAddr() {
	cerr<<"SocketAddr()\n";
}

SocketAddr::SocketAddr(const SocketAddr& sa):
	m_size(sa.m_size),
	m_domain(sa.m_domain),
	m_ip(sa.m_ip),
	m_port(sa.m_port){
	std::memcpy(&m_addr, &sa.m_addr, sa.m_size);
	cerr<<"SocketAddr(const SocketAddr&)\n";
}

SocketAddr& SocketAddr::operator= (const SocketAddr& sa){
	m_size = sa.m_size;
	m_domain = sa.m_domain;
	m_ip = sa.m_ip;
	m_port = sa.m_port;
	std::memcpy(&m_addr, &sa.m_addr, sa.m_size);
	cerr<<"operator=(const SocketAddr&)\n";
	return *this;
}

SocketAddr::SocketAddr(int domain,const string& ip, unsigned short int port):
    m_domain(domain),
    m_ip(ip),
    m_port(port){
    ::memset((&m_addr), 0, sizeof(m_addr));
    m_addr.sin_family = af_inet;
    m_addr.sin_port = ::htons(port);
    m_addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    m_size = sizeof(m_addr);
    m_sockaddr_ptr = (struct sockaddr *)&(m_addr);
	cerr<<"SocketAddr(int,const string&,unsigned short)\n";
}
SocketAddr::SocketAddr(struct sockaddr_in addr):m_addr(addr){
    m_size = sizeof(m_addr);
    m_domain = addr.sin_family;
    m_ip = string(::inet_ntoa(addr.sin_addr));
    m_port = ::ntohs(addr.sin_port);
    m_sockaddr_ptr = (struct sockaddr *)&(m_addr);
	cerr<<"SocketAddr(struct sockaddr_in)\n";
}
struct sockaddr* SocketAddr::get_sockaddr_ptr() const{
	cerr<<"get_sockaddr_ptr() const\n";
    return m_sockaddr_ptr;
}
unsigned int SocketAddr::get_sockaddr_size() const {
	cerr<<"get_sockaddr_size() const\n";
    return m_size;
}

Address SocketAddr::get_address() const {
	cerr<<"get_address() const\n";
    return move(Address(m_ip, m_port));
}

};
