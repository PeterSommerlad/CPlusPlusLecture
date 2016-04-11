#include <utility>
#include <iostream>

struct S {
	S(std::string const v = "default") : state{v} {
		std::cout << "creating S\n";
	}

	S(S const & s) : state {s.state} {
		std::cout << "copying S\n";
	}

	S(S&& s) : state {std::move(s.state)} {
		std::cout << "moving S\n";
	}

	std::string state;
};


void modify(S & s) {
	std::cout << "modifying lvalue reference: " << s.state << std::endl;
	s.state = "modified lvalue reference";
}

void modify(S && s) {
	std::cout << "modifying rvalue reference: " << s.state << std::endl;
	s.state = "modified rvalue reference";
}

void foo(int & i) {
	std::cout << "foo(int &)" << std::endl;
}

void foo(int && i) {
	std::cout << "foo(int &&)" << std::endl;
	foo(i);
}

int main(int argc, char **argv) {
	std::cout << "\t --- S s{} ---\n";
	S s{};
	std::cout << "\n";

	std::cout << "\t --- std::cout << s.state ---\n";
	std::cout << s.state << std::endl;
	std::cout << "\n";

	std::cout << "\t --- modify(s) ---\n";
	modify(s);
	std::cout << "\n";

	std::cout << "\t --- std::cout << s.state ---\n";
	std::cout << s.state << std::endl;
	std::cout << "\n";

	std::cout << "\t --- modify(std::move(s)) ---\n";
	modify(std::move(s));
	std::cout << "\n";

	std::cout << "\t !!! std::cout << s.state !!!\n";
	std::cout << s.state << std::endl; //While it is still valid we don't know its state...
	std::cout << "\n";

	std::cout << "\t !!! foo(1) !!!\n";
	foo(1);
	std::cout << "\n";
}

