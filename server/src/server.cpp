#include <utility> //std::pair
#include "server.h"

namespace jsondb {

Server::Server():
	m_ip("127.0.0.1"),
	m_port(8888),
	m_socket(af_inet, sock_stream),
	m_backlog(5){
}
Server::Server(const string& ip, unsigned short int port, int backlog):
	m_ip(ip),
	m_port(port),
	m_socket(af_inet, sock_stream),
	m_backlog(backlog){
}
Server::Server(const Server& s):
	m_ip(s.m_ip),
	m_port(s.m_port),
	m_socket(s.m_socket),
	m_backlog(s.m_backlog){
}

Server& Server::operator= (const Server& s){
	m_ip = s.m_ip;
	m_port = s.m_port;
	m_socket = s.m_socket;
	m_backlog = s.m_backlog;
	return *this;
}

void Server::run(){
	m_socket.bind(m_ip, m_port);
	m_socket.listen(m_backlog);
	socket_ns::Address addr(m_socket.getsockname());
	std::cout<<"ip:"<<addr.first<<" port:"<<addr.second<<'\n';
	while(true) {
		pair<Socket, Address> sa = m_socket.accept();
		Socket sock(sa.first);
		Address addr(sa.second);
		std::cout<<"accept()\n";
	}
}

};
