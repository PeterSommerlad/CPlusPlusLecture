#include <iostream>

struct S{};

void bar(int i) {
	std::cout << "bar(int)\n";
}

void bar(S * ps) {
	std::cout << "bar(S *)\n";
}


int main(int argc, char **argv) {
	bar(0);
//	bar(NULL);    //ambiguous
	bar(nullptr);
}
