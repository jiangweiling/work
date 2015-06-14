#ifndef SERVER_H
#define SERVER_H
#include <socket/socket.h>
#include "jsondb_ns.h"
#include <string>

namespace jsondb_ns {

using std::string;
using socket_ns::Socket;
using socket_ns::af_inet;
using socket_ns::sock_stream;
using socket_ns::Address;

class Server {
private:
	string m_ip;
	unsigned short int m_port;
	Socket m_socket;
	int m_backlog;
private:
	static bool initial; 
	static Server server;
private:
	Server()=default;
	Server(const string& ip, unsigned short int port, int backlog);
	Server(string&& ip, unsigned short int port, int backlog);
	Server& operator= (Server&& s);
public:
	Server& operator= (const Server& s) = delete;
	Server(const Server& s) = delete;
	static Server& get_server(const string& ip, unsigned short int port, int backlog);
	static Server& get_server(string&& ip, unsigned short int port, int backlog);
	static Server& get_server();
	int run();
};

};
#endif
