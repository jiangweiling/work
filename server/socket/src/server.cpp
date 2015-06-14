#include "server.h"

namespace socket_ns {

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


namespace socket_ns {

Server& Server::get_server(const string& ip, unsigned short int port, int backlog) {
	cerr<<"Server& Server::get_server(const string& ip, unsigned short int port, int backlog)\n";
	if(!initial) { //socket_ns::Server::initial
		server = move(Server(ip, port, backlog));
		initial = true;
	}
	cerr<<"Server& Server::get_server(const string& ip, unsigned short int port, int backlog)exit\n";
	return server;	
}

Server& Server::get_server(string&& ip, unsigned short int port, int backlog) {
	cerr<<"Server& Server::get_server(string&& ip, unsigned short int port, int backlog)\n";
	if(!initial) { //socket_ns::Server::initial
		server = Server(move(ip), port, backlog);
		initial = true;
	}
	cerr<<"Server& Server::get_server(string&& ip, unsigned short int port, int backlog)exit\n";
	return server;	
}
Server& Server::get_server() {
	return get_server("127.0.0.1", 8888, 10);
}

void Server::socket_push(const Socket& s) {
	cerr<<"void Server::socket_push(const Socket& s)\n";
	lock_guard<mutex> lck(m_mutex);
	m_socket_queue.push(s);
	cerr<<"void Server::socket_push(const Socket& s)exit\n";
}

Socket Server::socket_pop() {
	cerr<<"Socket Server::socket_pop()\n";
	lock_guard<mutex> lck(m_mutex);
	Socket s = m_socket_queue.front();
	m_socket_queue.pop();
	cerr<<"Socket Server::socket_pop()exit\n";
	return s;
}
bool Server::socket_empty(){
	cerr<<"bool Server::socket_empty() const\n";
	lock_guard<mutex> lck(m_mutex);
	bool flag = m_socket_queue.empty();
	cerr<<"bool Server::socket_empty() const exit\n";
	return flag;
}
int Server::run(){
	cerr<<"int Server::run()\n";
	int bind_flag = m_socket.bind(m_ip, m_port);
	if(bind_flag){
		cerr<<"ip = "<<m_ip<<endl
			<<"port = "<<m_port<<endl;
		cerr<<strerror(errno)<<endl;
	}
	m_socket.listen(m_backlog);
	socket_ns::Address addr(m_socket.getsockname());
	cout<<"bind at address: "<<addr<<endl;
	while(true) {
		Socket s = m_socket.accept();
		cout<<s<<endl;
		socket_push(s);
	}
	cerr<<"int Server::run()exit\n";
	return 0;
}

};
