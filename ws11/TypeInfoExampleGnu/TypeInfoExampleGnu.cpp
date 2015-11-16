#include <typeinfo>
#include <iostream>
#include <string>
#include <cxxabi.h> // __cxa_demangle

std::string demangle(char const *name){
	char *toBeFreed = __cxxabiv1::__cxa_demangle(name,0,0,0);
	std::string result(toBeFreed);
	::free(toBeFreed);
	return result;
}

template <typename T>
void printIdRef(T const & t) {
	std::cout << "printIdRef(T const &t): " << demangle(typeid(t).name()) << std::endl;
}
template <typename T>
void printIdVal(T t) {
	std::cout << "printIdVal(T t): " << demangle(typeid(t).name()) << std::endl;
}

struct Double { double d;};

int main(){
	printIdRef("hello");
	printIdVal("hello");
	printIdRef(Double{});
	printIdVal(Double{});
}
