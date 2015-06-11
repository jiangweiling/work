#ifndef SOCKET_NS_H
#define SOCKET_NS_H
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include <string>
#include <iostream>
using std::string;
using std::pair;
using std::cout;
using std::cerr;
using std::endl;

const int __AF_INET = AF_INET;
#undef AF_INET
const int AF_INET = __AF_INET;

namespace socket_ns {

const int AF_INET = ::AF_INET;
const int SOCK_STREAM = ::SOCK_STREAM;
const int SOCK_DGRAM = ::SOCK_DGRAM;
const int BUFSIZE = 1024;

typedef pair<string, int> Address;

};
#endif //SOCKET_NS_H
