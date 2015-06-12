#ifndef SERVER_H
#define SERVER_H
#include <socket/socket.h>

#include <string>

namespace jsondb {

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
public:
	Server();
	Server(const string& ip, unsigned short int port, int backlog);
	Server(const Server& s);
	Server& operator= (const Server& s);
	int run();
};

};
#endif
