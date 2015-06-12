#include "server.h"
#include <iostream>
#include <thread>
#include <chrono>
using std::thread;
using std::cout;
using std::endl;
using jsondb::Server;

int main() {
	Server s;
	auto bg = [&s](){s.run();};
	thread t(bg);
	t.join();
	//t.detach();
	cout<<"test"<<endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return 0;
}
