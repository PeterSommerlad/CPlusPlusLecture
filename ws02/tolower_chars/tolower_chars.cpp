#include <iostream>
#include <cctype>
int main() {
	char c{};
	while(std::cin.get(c)){
		std::cout.put(std::tolower(c));
	}
}
