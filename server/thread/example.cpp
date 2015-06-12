#include <iostream>
#include <string>
#include <vector>
#include <thread>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::thread;
class A{
public:
	void run(){
		cout<<"A::run\n";
	}

};
int main() {
	int a(0);
	auto bg = [](A& a){a.run();};
	bg(a);
	cout<<a;
	thread t(bg, a);
	t.join();
	return 0;
}
