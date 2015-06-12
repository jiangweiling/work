#ifndef SERVER_H
#define SERVER_H
#include <socket/socket.h>

#include <string>

namespace jsondb {

using std::string;
using std::pair;
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
	Server(const Server& s);
	Server& operator= (const Server& s);
	void run();
};

};
#endif
