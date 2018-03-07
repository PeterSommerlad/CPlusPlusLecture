#include <utility>
#include <iostream>

struct S {
	S() {
		std::cout << "Constructor S()\n";
	}

//	S(S const &) = delete;


//	S(S const &) = delete;
//	S(S &&) = delete;
	S(S const &) {
		std::cout << "Constructor S(S const &)\n";
	}

	S(S &&) {
		std::cout << "Constructor S(S &&)\n";
	}

	S & operator =(S const &) {
		std::cout << "operator =(S const &)\n";
		return *this;
	}

	S & operator =(S &&) {
		std::cout << "operator =(S &&)\n";
		return *this;
	}
};

S create() {
	S s{};
	std::cout << "\t --- create() ---\n";
	return std::move(s);
}

int main() {
	std::cout << "\t --- S s{create()} ---\n";
	S s{create()};
}

