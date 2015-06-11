#include "src/hello.h"
#include <pthread.h>

int main(int argc, char* argv) {
	say_hello();
	pthread_t pt;
	return 0;
}
