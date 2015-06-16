#include <iostream>
#include <string>
#include <thread>
#include <socket/server.h>
//#include <socket/socket_epoll.h>
//#include <socket/stream_hub.h>
#include <sstream>
using std::stringstream;

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::thread;
using namespace socket_ns;
void server_test() {
	Server& server = Server::get_server("172.18.219.115",8888);
	auto server_bg = [&server](){server.run();};
	thread t(server_bg);
	t.join();
}
/*
void epoll_test() {
	Server& server = Server::get_server("172.18.219.115",18888);
	auto server_bg = [&server](){server.run();};
	thread st(server_bg);
	SocketEpoll se;
	for(int i=0; i < 60; ++i) {
		while(!server.socket_empty()){
			se.add(server.socket_pop_all());
		}
		se.wait(2000);
	}
	st.join();
}
void streamhub_test() {
	Server& server = Server::get_server("172.18.219.115",18888);
	auto server_bg = [&server](){server.run();};
	thread t1(server_bg);
	SocketEpoll se;
	StreamHub& hub = StreamHub::get_hub();
	while(true){
		while(!server.socket_empty()){
			se.add(server.socket_pop_all());
		}
		se.remove(hub.push(se.wait(2000)));
		
	}
	t1.join();
}
*/
int main() {
	server_test();
	return 0;
}
