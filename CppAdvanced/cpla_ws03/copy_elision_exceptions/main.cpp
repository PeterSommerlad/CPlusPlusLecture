#include <utility>
#include <iostream>

struct S {
	S() {
		std::cout << "creating S\n";
	}

//	S(S const &) = delete;

	S(S const &) noexcept {
		std::cout << "copying S\n";
	}
};


int main() {
	try {
		S s{};
		throw s;
	} catch (S s) {
	}
}

