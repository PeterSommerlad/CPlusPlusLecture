#include <iostream>
#include <iomanip>
#include <cmath>
int main() {
	std::cout << 42 << '\t'
	          << std::oct << 42 << '\t'
	          << std::hex << 42 << '\n';
	std::cout << 42 << '\t' // std::hex is sticky
	          << std::dec << 42 << '\n';
	std::cout << std::setw(10) << 42
	          << std::left<< std::setw(5)<< 43 << "*\n";
	std::cout << std::setw(10) << "hallo"<<"*\n";

	double const pi{std::acos(0.5)*3};
	std::cout << std::setprecision(4) << pi << '\n';
	std::cout << std::scientific << pi <<  '\n';
	std::cout << std::fixed << pi*1e6 <<  '\n';
}
