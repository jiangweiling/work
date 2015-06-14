#include "server.h"
#include <iostream>
#include <thread>
#include <chrono>
using std::thread;
using std::cout;
using std::endl;
using jsondb_ns::Server;

int main() {
	Server& s = Server::get_server();
	auto bg = [&s](){s.run();};
	thread t(bg);
	t.join();
	//t.detach();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	return 0;
}
