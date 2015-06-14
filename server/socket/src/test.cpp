#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "server.h"
#include "socket_epoll.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::thread;
using namespace socket_ns;
int main() {
	SocketEpoll se;	
	Server& server = Server::get_server();
	auto server_bg = [&server](){server.run();};
	thread server_t(server_bg);
	for(int i=0; i < 6000; ++i) {
		while(!server.socket_empty()){
			se.add(server.socket_pop());
		}
		se.wait(20000);
	}
	server_t.join();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	return 0;
}
