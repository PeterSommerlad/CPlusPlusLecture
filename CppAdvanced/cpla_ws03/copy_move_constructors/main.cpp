#include <utility>
#include <iostream>

struct S {
	S() {
		std::cout << "creating S\n";
	}

	S(S const &) {
		std::cout << "copying S\n";
	}

	S(S&&) {
		std::cout << "moving S\n";
	}
};


int main() {
	std::cout << "\t --- S s{} ---\n";
	S s{};

	std::cout << "\t --- S copy{s} ---\n";
	S copy{s};

	std::cout << "\t --- S move{std::move(s)} ---\n";
	S move{std::move(s)};
}

