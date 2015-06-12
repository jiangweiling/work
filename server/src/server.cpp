#include <utility> //std::pair
#include "server.h"

namespace jsondb {

Server::Server():m_socket(af_inet, sock_stream) {
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
	m_backlog = 5;
	m_socket.bind("127.0.0.1",9999);
	m_socket.listen(m_backlog);
	socket_ns::Address addr(m_socket.getsockname());
	std::cout<<"ip:"<<addr.first<<" port:"<<addr.second<<'\n';
	while(true) {
		pair<Socket, Address> sa = m_socket.accept();
		Socket sock(sa.first);
		Address addr(sa.second);
		std::cout<<"accept()\n";
		break;
	}
}

};
