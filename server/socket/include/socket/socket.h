#ifndef SOCKET_H
#define SOCKET_H
#include "socket_ns.h"
#include "socket_addr.h"
#include "unique_socket.h"

namespace socket_ns {

class Socket {
private:
	shared_ptr<UniqueSocket> socket_ptr;
public:
    Socket();
    Socket(int domain, int type, int protocol);
    Socket(int domain, int type);
    Socket(int socket_fd);

	Socket(const UniqueSocket& s) = delete;
	Socket(UniqueSocket&& s);
	Socket& operator=(const UniqueSocket& s) = delete;
	Socket& operator=(UniqueSocket&& s);

    int bind(const char* ip, unsigned short int port);
    int bind(const string& ip, unsigned short int port);
    int bind(string&& ip, unsigned short int port);
    int bind(const string& ip);
    int bind(string&& ip);
    int bind(const char* ip);
    int connect(const char* ip, unsigned short int port);
    int connect(const string& ip, unsigned short int port);
    int connect(string&& ip, unsigned short int port);
    int listen(int backlog);
    int listen();
    Socket accept();
	int setblocking(bool block);
	bool block();
    int send(const string& data) const;
    int send(string&& data) const;
    int recv(string& data) const;
	int get_fd() const;
    Address getsockname() const;
    Address getpeername() const;
};

};

namespace socket_ns {

ostream& operator<< (ostream& os, const Socket& s);
ostream& operator<< (ostream& os, Socket&& s);

};
#endif //UNIQUE_SOCKET_H
