#include <iostream>
#include <string>
#include "unique_socket.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using socket_ns::UniqueSocket;
int main() {
	UniqueSocket s;	
	cout<<s<<endl;
	cout<<"block:"<<s.block()<<endl;
	s.setblocking(false);
	cout<<"block:"<<s.block()<<endl;
	s.bind("127.0.0.1", 8888);
	s.listen(5);
	s.accept();
	return 0;
}
