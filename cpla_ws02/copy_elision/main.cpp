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

S boiler(S s) {
	return s;
}

S create() {
	return S{};
}

int main(int argc, char **argv) {
	std::cout << "\t --- S copy{S{}} ---\n";
	S copy{S{}};

	std::cout << "\t --- S hot_s{create()} ---\n";
	S new_sw{create()};

	std::cout << "\t --- S hot_s{boiler(S{})} ---\n";
	S hot_s{boiler(S{})};
}

