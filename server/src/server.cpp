#include "server.h"

namespace jsondb_ns {

bool Server::initial = false;
Server Server::server;

Server::Server(const string& ip, unsigned short int port, int backlog):
	m_ip(ip),
	m_port(port),
	m_socket(af_inet, sock_stream),
	m_backlog(backlog){
	cerr<<"Server::Server(const string& ip, unsigned short int port, int backlog)\n";
	cerr<<"Server::Server(const string& ip, unsigned short int port, int backlog)exit\n";
}

Server::Server(string&& ip, unsigned short int port, int backlog):
	m_ip(move(ip)),
	m_port(port),
	m_socket(af_inet, sock_stream),
	m_backlog(backlog){
	cerr<<"Server::Server(string&& ip, unsigned short int port, int backlog)\n";
	cerr<<"Server::Server(string&& ip, unsigned short int port, int backlog)exit\n";
}

Server& Server::operator= (Server&& s) {
	cerr<<"Server& Server::operator= (Server&& s)\n";
	m_ip = move(s.m_ip);
	m_port = s.m_port;
	m_socket = move(s.m_socket);
	m_backlog = s.m_backlog;
	cerr<<"Server& Server::operator= (Server&& s)exit\n";
	return *this;
}
};


namespace jsondb_ns {

Server& Server::get_server(const string& ip, unsigned short int port, int backlog) {
	cerr<<"Server& Server::get_server(const string& ip, unsigned short int port, int backlog)\n";
	if(!initial) { //jsondb_ns::Server::initial
		server = move(Server(ip, port, backlog));
		initial = true;
	}
	cerr<<"Server& Server::get_server(const string& ip, unsigned short int port, int backlog)exit\n";
	return server;	
}

Server& Server::get_server(string&& ip, unsigned short int port, int backlog) {
	cerr<<"Server& Server::get_server(string&& ip, unsigned short int port, int backlog)\n";
	if(!initial) { //jsondb_ns::Server::initial
		server = Server(move(ip), port, backlog);
		initial = true;
	}
	cerr<<"Server& Server::get_server(string&& ip, unsigned short int port, int backlog)exit\n";
	return server;	
}
Server& Server::get_server() {
	return get_server("127.0.0.1", 8888, 10);
}
int Server::run(){
	cerr<<"int Server::run()\n";
	m_socket.bind(m_ip, m_port);
	m_socket.listen(m_backlog);
	socket_ns::Address addr(m_socket.getsockname());
	cout<<"in Server::run() address: "<<addr<<endl;
	while(true) {
		Socket s = m_socket.accept();
		Address addr(s.getpeername());
		std::cout<<"peer addr: "<<addr.first<<" "<<addr.second<<"\n";
		std::cout<<"accept()\n";
		break;
	}
	cerr<<"int Server::run()exit\n";
	return 0;
}

};
