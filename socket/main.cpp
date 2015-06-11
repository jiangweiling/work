#include "socket.h"
#include <iostream>
using std::cout;
using std::endl;
int main(int argc, char* argv[]) {
    socket_ns::Socket s(socket_ns::AF_INET, socket_ns::SOCK_STREAM);
    cout<<"s.bind = "<<s.bind("127.0.0.1", 13456)<<endl;
    socket_ns::Address addr(s.getsockname());
    cout<<addr.first<<endl<<addr.second<<endl;
    cout<<"s.listen = "<<s.listen(5)<<endl;
    cerr<<strerror(errno)<<endl;
    return 0;
}

