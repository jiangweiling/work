#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#include <socket_ns.h>
#include <socket.h>

using namespace std;
using namespace socket_ns;

void socket_test(){
	Socket s;
	s.bind("172.18.219.115");
	s.listen();
	auto conn = s.accept();
	cout<<conn<<endl;
	string data;
	conn.recv(data);
	cout<<data<<endl;
}
void usocket_test(){
	UniqueSocket us;
	us.bind("172.18.219.115");
	us.listen();
	UniqueSocket usconn(us.accept());
	cout<<usconn<<endl;
	string data;
	usconn.recv(data);
	cout<<data<<endl;
}
int main() {
	socket_test();
	return 0;
}
