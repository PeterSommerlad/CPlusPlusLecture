#include <iostream>
#include <boost/type_index.hpp>

struct S {
	S() = default;
	S(S const &) {
		std::cout << "S(S const &) -> copy\n";
	}
	S(S&&) {
		std::cout << "S(S &&) -> move\n";
	}
};

void do_something(S const &) {
	std::cout << "do_something(S const &)\n";
}
void do_something(S&&) {
	std::cout << "do_something(S &&)\n";
}

template<typename T>
void log_and_do(T & t) {
	std::cout << "logging!\n";
	do_something(t);
}


int main(int argc, char **argv) {
	S s{};

	std::cout << "--- calling log_and_do(s)\n";
	log_and_do(s); //lvalue

	std::cout << "--- calling log_and_do(S{})\n";
//	log_and_do(S{}); //rvalue - does not compile

	std::cout << "--- end\n";
}
