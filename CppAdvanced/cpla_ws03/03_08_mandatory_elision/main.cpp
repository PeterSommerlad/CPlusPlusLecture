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

	S(S &&) {
		std::cout << "moving S\n";
	}
};

S boiler(S s) {
	return s;
}

S create() {
	return S{};
}

int main() {
	std::cout << "\t --- S copy{S{}} ---\n";
	S s = S{S{}};

	std::cout << "\t --- S new_sw{create()} ---\n";
	S new_sw{create()};

	std::cout << "\t --- S * sp = new S{create()} ---\n";
	S * sp = new S{create()};

	std::cout << "\t --- S hot_s{boiler(S{})} ---\n";
	S hot_s{boiler(S{})};
}

