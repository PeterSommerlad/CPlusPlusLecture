#include <iostream>
#include <utility>

struct S {
	S() = default;
	S(S const &) {
		std::cout << "S(S const&)\n";
	}
	S(S&&) {
		std::cout << "S(S&&)\n";
	}
	S& operator=(S&&) {
		std::cout << "operator=(S&&)\n";
		return *this;
	}
};

S createS(S & s) {
	return s;
}

//void f(S param) {
//	std::cout << "f(S)\n";
//}

void f(S & param) {
	std::cout << "f(S &)\n";
}

void f(S const & param) {
	std::cout << "f(S const &)\n";
}

void f(S && param) {
	std::cout << "f(S &&)\n";
}

int main(int argc, char **argv) {
	S s{};
	f(s);

	S const cs{};
	f(cs);

	f(S{});

	f(std::move(s));

	f(createS(s));
}

