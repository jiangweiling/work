#ifndef SOCKET_NS_H
#define SOCKET_NS_H
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <errno.h>

#include <cstring> 
#include <utility> 
#include <string> 
#include <iostream>

using std::string;
using std::pair;
using std::cout;
using std::cerr;
using std::endl;
using std::memset;

namespace socket_ns {

const int af_inet = AF_INET;
const int sock_stream = SOCK_STREAM;
const int sock_dgram = SOCK_DGRAM;
const int buf_size = 1024;

typedef pair<string, int> Address;

};

#endif //SOCKET_NS_H
