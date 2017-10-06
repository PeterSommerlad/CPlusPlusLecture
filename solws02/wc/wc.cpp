#include <iostream>
#include <string>

unsigned wc(std::istream & input) {
	unsigned count{0};
	std::string word{};
	while (input >> word) {
		count++;
	}
	return count;
}

int main() {
	std::cout << wc(std::cin);
}
