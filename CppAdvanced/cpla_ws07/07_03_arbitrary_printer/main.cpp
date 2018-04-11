#include<iostream>
#include <string>

void printAll() {
}

template<typename First, typename...Types>
void printAll(First const & first, Types const &...rest) {
	std::cout << first;
	if (sizeof...(Types)) {
		std::cout << ", ";
	}
	printAll(rest...);
}


int main(int argc, char **argv) {
	int i { 42 };
	double d { 1.25 };
	std::string book { "Lucid C++" };
	printAll(i, d, book);
}

