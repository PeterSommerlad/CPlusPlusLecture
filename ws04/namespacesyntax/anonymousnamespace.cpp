#include <iostream>
namespace { // anonymous
void doit(){ // can not be called outside this file
	std::cout << "doit called\n";
}
} // anonymous namespace ends
void print(){ // callable from other parts if declared
	doit();
	std::cout << "print called\n";
}
