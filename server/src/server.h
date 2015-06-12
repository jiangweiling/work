#ifndef SERVER_H
#define SERVER_H
#include <socket/socket.h>
class Server {
private:
	socket_ns::Socket m_socket;
public:
	Server();
};
#endif
