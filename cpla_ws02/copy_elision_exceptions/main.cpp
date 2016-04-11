#include <utility>
#include <iostream>

struct S {
	S() {
		std::cout << "creating S\n";
	}

//	S(S const &) = delete;

	S(S const &) {
		std::cout << "copying S\n";
	}
};


int main(int argc, char **argv) {
	try {
		throw S{};
	} catch (S s) {

	}
}

