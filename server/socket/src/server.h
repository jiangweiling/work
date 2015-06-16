#ifndef SERVER_H
#define SERVER_H
#include "socket.h"
#include "socket_ns.h"

namespace socket_ns {

class Server {
private:
	string m_ip;
	unsigned short int m_port;
	Socket m_socket;
	int m_backlog;
	vector<Socket> m_sockets;
	mutex m_mutex;
private:
	static bool initial; 
	static Server server;
private:
	Server();
	Server(const string& ip, unsigned short int port, int backlog);
	Server(string&& ip, unsigned short int port, int backlog);
	Server& operator= (Server&& s);
	void socket_push(const Socket& s);

public:
	Server& operator= (const Server& s) = delete;
	Server(const Server& s) = delete;
	static Server& get_server(const string& ip, unsigned short int port, int backlog=10);
	static Server& get_server(string&& ip, unsigned short int port, int backlog=10);
	static Server& get_server();
	Socket socket_pop_one();
	vector<Socket> socket_pop_all();
	bool socket_empty();
	int run();
};

};
#endif
