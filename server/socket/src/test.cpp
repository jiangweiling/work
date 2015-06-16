#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "server.h"
#include "socket_epoll.h"
#include "msg_hub.h"

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
void msghub_test() {
	Server& server = Server::get_server("172.18.219.115",18888);
	auto server_bg = [&server](){server.run();};
	thread t1(server_bg);
	SocketEpoll se;
	MsgHub& mh = MsgHub::get_msghub();
	while(true){
		while(!server.socket_empty()){
			se.add(server.socket_pop_all());
		}
		se.remove(mh.push(se.wait(2000)));
		
	}
	t1.join();
}

int main() {
	msghub_test();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	return 0;
}
