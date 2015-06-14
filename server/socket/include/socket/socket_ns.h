#ifndef SOCKET_NS_H
#define SOCKET_NS_H
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <fcntl.h>
#include <unistd.h> 
#include <errno.h>

#include <cstring> 
#include <utility> 
#include <string> 
#include <memory>
#include <iostream>


namespace socket_ns {

using std::string;        // string
using std::pair;          // utility
using std::cout;          // iostream
using std::cerr;          // iostream
using std::endl;          // iostream
using std::memset;        // cstring
using std::memcpy;        // cstring
using std::move;          // utility
using std::ostream;       //iostream
using std::shared_ptr;    //memory

const int af_inet = AF_INET;           // sys/socket.h
const int sock_stream = SOCK_STREAM;   // sys/socket.h
const int sock_dgram = SOCK_DGRAM;     // sys/socket.h
const int buf_size = 1024;

typedef pair<string, unsigned short int> Address;

};

#endif //SOCKET_NS_H
