#include <iostream>

int main() {
	auto ptr=new int{5};
	std::cout << *ptr << '\n';
	delete ptr;
}
