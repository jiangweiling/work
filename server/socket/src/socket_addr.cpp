#include "socket_addr.h"
namespace socket_ns {

void SocketAddr::m_addr_ctor(int domain, const char* ip, unsigned short int port) {
	cerr<<"void SocketAddr::m_addr_ctor(int domain, const char* ip, unsigned short int port)\n";
    m_size = sizeof(m_addr);
	memset(&m_addr, 0, m_size); // cstring
    m_addr.sin_family = domain;
    m_addr.sin_addr.s_addr = ::inet_addr(ip);  // arpa/inet.h
    m_addr.sin_port = ::htons(port);  // arpa/inet.h
	cerr<<"void SocketAddr::m_addr_ctor(int domain, const char* ip, unsigned short int port)exit\n";
}
SocketAddr::SocketAddr():
	m_domain(af_inet),
	m_ip("0.0.0.0"),
	m_port(0) {
	cerr<<"SocketAddr()\n";
	m_addr_ctor(m_domain, m_ip.c_str(), m_port);
	cerr<<"SocketAddr()exit\n";
}

SocketAddr::SocketAddr(int domain,const string& ip, unsigned short int port):
    m_domain(domain),
    m_ip(ip),
    m_port(port){
	cerr<<"SocketAddr(int,const string&,unsigned short)\n";
	m_addr_ctor(m_domain, m_ip.c_str(), m_port);
	cerr<<"SocketAddr(int,const string&,unsigned short)exit\n";
}

SocketAddr::SocketAddr(int domain,const char* ip, unsigned short int port):
    m_domain(domain),
    m_ip(ip),
    m_port(port){
	cerr<<"SocketAddr(int,const char*,unsigned short)\n";
	m_addr_ctor(m_domain, ip, m_port);
	cerr<<"SocketAddr(int,const char*,unsigned short)exit\n";
}

SocketAddr::SocketAddr(int domain, string&& ip, unsigned short int port):
    m_domain(domain),
    m_port(port){
	cerr<<"SocketAddr(int,string&&,unsigned short)\n";
    swap(m_ip,ip);
	m_addr_ctor(m_domain, m_ip.c_str(), m_port);
	cerr<<"SocketAddr(int,string&&,unsigned short)exit\n";
}

SocketAddr::SocketAddr(const string& ip, unsigned short int port):
    m_domain(af_inet),  //socket_ns::af_inet
    m_ip(ip),
    m_port(port){
	cerr<<"SocketAddr(const string&,unsigned short)\n";
	m_addr_ctor(m_domain, m_ip.c_str(), m_port);
	cerr<<"SocketAddr(const string&,unsigned short)exit\n";
}

SocketAddr::SocketAddr(const char* ip, unsigned short int port):
    m_domain(af_inet),  //socket_ns::af_inet
    m_ip(ip),
    m_port(port){
	cerr<<"SocketAddr(const char*,unsigned short)\n";
	m_addr_ctor(m_domain, ip, m_port);
	cerr<<"SocketAddr(const char*,unsigned short)exit\n";
}

SocketAddr::SocketAddr(string&& ip, unsigned short int port):
    m_domain(af_inet),  //socket_ns::af_inet
    m_port(port){
	cerr<<"SocketAddr(string&&,unsigned short)\n";
    swap(m_ip,ip);
	m_addr_ctor(m_domain, m_ip.c_str(), m_port);
	cerr<<"SocketAddr(string&&,unsigned short)exit\n";
}

SocketAddr::SocketAddr(const SocketAddr& sa):
	m_size(sa.m_size),
	m_domain(sa.m_domain),
	m_ip(sa.m_ip),
	m_port(sa.m_port){
	cerr<<"SocketAddr(const SocketAddr&)\n";
	memcpy(&m_addr, &sa.m_addr, sa.m_size); // cstring
	cerr<<"SocketAddr(const SocketAddr&)exit\n";
}

SocketAddr::SocketAddr(SocketAddr&& sa):
	m_size(sa.m_size),
	m_domain(sa.m_domain),
	m_port(sa.m_port){
	cerr<<"SocketAddr(const SocketAddr&&)\n";
	swap(m_ip,sa.m_ip);
	memcpy(&m_addr, &sa.m_addr, sa.m_size); // cstring
	cerr<<"SocketAddr(const SocketAddr&&)exit\n";
}


SocketAddr::SocketAddr(struct sockaddr_in addr):
	m_addr(addr),
    m_size(sizeof(m_addr)),
    m_domain(addr.sin_family),
    m_ip(::inet_ntoa(addr.sin_addr)),  // arpa/inet.h
    m_port(::ntohs(addr.sin_port)){    // arpa/inet.h
	cerr<<"SocketAddr(struct sockaddr_in)\n";
	cerr<<"SocketAddr(struct sockaddr_in)exit\n";
}

};

namespace socket_ns {

SocketAddr& SocketAddr::operator= (const SocketAddr& sa){
	cerr<<"operator=(const SocketAddr&)\n";
	memcpy(&m_addr, &sa.m_addr, sa.m_size); // cstring
	m_size = sa.m_size;
	m_domain = sa.m_domain;
	m_ip = sa.m_ip;
	m_port = sa.m_port;
	cerr<<"operator=(const SocketAddr&)exit\n";
	return *this;
}

SocketAddr& SocketAddr::operator= (SocketAddr&& sa){
	cerr<<"operator=(SocketAddr&&)\n";
	memcpy(&m_addr, &sa.m_addr, sa.m_size); // cstring
	m_size = sa.m_size;
	m_domain = sa.m_domain;
	swap(m_ip,sa.m_ip); //utility
	m_port = sa.m_port;
	cerr<<"operator=(SocketAddr&&)exit\n";
	return *this;
}

};

namespace socket_ns {

struct sockaddr* SocketAddr::get_sockaddr_ptr() const{
	cerr<<"get_sockaddr_ptr() const\n";
	cerr<<"get_sockaddr_ptr() const exit\n";
    return (struct sockaddr *)&(m_addr);
}
unsigned int SocketAddr::get_sockaddr_size() const {
	cerr<<"get_sockaddr_size() const\n";
	cerr<<"get_sockaddr_size() const exit\n";
    return m_size;
}

Address SocketAddr::get_address() const {
	cerr<<"get_address() const\n";
	cerr<<"get_address() const exit\n";
    return move(Address(m_ip, m_port)); //utility
}

};

namespace socket_ns {

ostream& operator<< (ostream& os, const Address& addr){
	os<<"< ip = "<<addr.first<<", port = "<<addr.second<<" >";
	return os;
}
ostream& operator<< (ostream& os, Address&& addr){
	os<<"< ip = "<<addr.first<<", port = "<<addr.second<<" >";
	return os;
}

ostream& operator<< (ostream& os, const SocketAddr& sa){
	auto addr = sa.get_address();
	os<<"< ip = "<<addr.first<<", port = "<<addr.second<<" >";
	return os;
}
ostream& operator<< (ostream& os, SocketAddr&& sa){
	auto addr = sa.get_address();
	os<<"< ip = "<<addr.first<<", port = "<<addr.second<<" >";
	return os;
}

};
