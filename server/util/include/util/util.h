#ifndef UTIL_H
#define UTIL_H
#include <cstring>
using std::memcpy;  // cstring

namespace util_ns {

bool bit2int(const void* buffer, unsigned int size, unsigned int& value);
bool int2bit(unsigned int value, void* buffer, unsigned int size);

};
#endif

