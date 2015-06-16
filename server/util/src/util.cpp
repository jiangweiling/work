#include "util.h"
namespace util_ns {

bool bit2int(const void* buffer, unsigned int size, unsigned int& value){
	if( !buffer || sizeof(value) > size ){
		return false;
	}
	memcpy(&value, buffer, sizeof(value));
	return true;
}

bool int2bit(unsigned int value, void* buffer, unsigned int size){
	if( !buffer || sizeof(value) > size ){
		return false;
	}
	memcpy(buffer, &value, sizeof(value));
	return true;
}

};
