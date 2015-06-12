#include "server.h"
#include <thread>
#include <chrono>
using std::thread;
using std::cout;
using std::endl;
using jsondb::Server;
auto bg = [](Server& s){s.run();};
int main() {
	Server s;
	thread t(bg, s);
	t.join();
	//t.detach();
	//cout<<"test"<<endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return 0;
}
