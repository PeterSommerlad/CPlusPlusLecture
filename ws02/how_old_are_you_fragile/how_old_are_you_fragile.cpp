#include <iostream>
int main() {
	std::cout << "Enter your age: " << std::flush;
	int age{-1};
	std::cin >> age;
	std::cout << "\nYou are " << age
			  << " years old\n";
}

