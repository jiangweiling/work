#ifndef SOCKET_H
#define SOCKET_H
#include "socket_ns.h"
#include "socket_addr.h"
#include "unique_socket.h"

namespace socket_ns {

class Socket {
private:
	shared_ptr<UniqueSocket> m_socket_ptr;
public:
    Socket(shared_ptr<UniqueSocket> socket_ptr=nullptr);
    Socket(int domain, int type, int protocol=0);
    Socket(int socket_fd);

	Socket(const Socket& s);
	Socket(Socket&& s);
	Socket& operator=(const Socket& s);
	Socket& operator=(Socket&& s);

    int bind(const char* ip, unsigned short int port = 0);
    int bind(const string& ip, unsigned short int port = 0);
    int bind(string&& ip, unsigned short int port = 0);
    int connect(const char* ip, unsigned short int port);
    int connect(const string& ip, unsigned short int port);
    int connect(string&& ip, unsigned short int port);
    int listen(int backlog = 10);
    Socket accept();
	int setblocking(bool block);
	bool block();
    int send(const char* data) const;
    int send(const string& data) const;
    int send(string&& data) const;
    bool recv(string& data) const;
	int get_fd() const;
    Address getsockname() const;
    Address getpeername() const;
	shared_ptr<UniqueSocket> get_socket_ptr() const;
};

};

namespace socket_ns {

ostream& operator<< (ostream& os, const Socket& s);
ostream& operator<< (ostream& os, Socket&& s);

};
#endif //UNIQUE_SOCKET_H
