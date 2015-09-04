#include <iostream>

int main() {
	double x = 45/8;
	std::cout << "45/8=" <<x<<'\n';
//	std::cout << "UB 5%0" << int(x)%0 << '\n'; // UB, can crash
}
