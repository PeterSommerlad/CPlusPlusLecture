#include <iostream>
#include <string>
#include <cxxabi.h> // __cxa_demangle

void foo(){}
struct bar{
	void operator()(){}
};

void match(bool b){
	std::cout << (b?"":"no ") << "match"<<std::endl;
}

std::string demangle(char const *name){
	char *toBeFreed = __cxxabiv1::__cxa_demangle(name,0,0,0);
	std::string result(toBeFreed);
	::free(toBeFreed);
	return result;
}

int main(){
	using namespace std;
	cout << demangle(typeid(&foo).name()) << endl;
	cout << demangle(typeid(bar()).name()) << endl;
	cout << demangle(typeid((bar())).name()) << endl;
	match (typeid(foo) == typeid(void()));
	match(typeid(foo) == typeid((bar())()));
}
