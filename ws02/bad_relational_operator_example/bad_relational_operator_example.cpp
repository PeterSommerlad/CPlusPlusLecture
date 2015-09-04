#include <iostream>

int main() {
	std::cout << "enter a number : " ;
	int a{};
	std::cin >> a;
	if (0<a<10){
		std::cout << "small positve a " << a << '\n';
	} else {
		std::cout << "large or very small a " << a << '\n';
	}
}
