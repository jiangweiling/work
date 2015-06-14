#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "server.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::thread;
using namespace socket_ns;
void print(Server* s){
	for(int i = 0; i < 30; ++i){
		cout<<"i="<<i<<endl;
		if(!s->socket_empty()) {
			Socket sock = s->socket_pop();
			cout<<sock<<endl;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
};
int main() {
	Server& s = Server::get_server();
	auto bg = [&s](){s.run();};
	thread t(bg);
	thread t1(print,&s);
	t.join();
	t1.join();
	//t.detach();
	std::this_thread::sleep_for(std::chrono::seconds(30));
	return 0;
}
