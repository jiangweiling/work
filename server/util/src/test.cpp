#include <iostream>
#include "util.h"
using namespace std;;
using namespace util_ns;
int main() {
	unsigned int a=9999999;
	cin>>a;
	char str[4];
	int2bit(a,str,4);
	unsigned int b;
	bit2int(str,4,b);
	cout<<b<<endl;
	return 0;
}
