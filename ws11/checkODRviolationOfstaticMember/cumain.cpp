#include "templatewithstaticmember.h"
#include <iostream>

int foo();

int main(){
	std::cout << staticmember<double>::dummy << '\n';
	std::cout << staticmember<int>::dummy << '\n';
	std::cout << foo() << '\n';
	std::cout << staticmember<int>::dummy << '\n';
}
