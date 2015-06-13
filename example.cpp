#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
class A{
public:
	int m_a;
	A(int a){
		m_a = 10;
		cout<<"A(int)\n";
	}
	A(){
		m_a = 2;
		cout<<"A()\n";
	}
	A(const A& a){
		m_a = 3;
		cout<<"A(const A&)\n";
	}
	A(const A&& a){
		m_a = 4;
		cout<<"A(const A&&)\n";
	}
	A(A&& a){
		m_a = 5;
		cout<<"A(A&&)\n";
	}
};
void print(int && v) {
	cout<<"int &&v"<<endl;
}
void print(int & v) {
	cout<<"int &v"<<endl;
}
template<typename T>
void test(T && v){
	print(std::forward<T>(v));
	cout<<endl;
}
int main() {
	return 0;
}
