#include <iostream>
#include <utility>

struct S {
//	void m() {
//		std::cout << "m()\n";
//	}
//	void m() const {
//		std::cout << "m() const\n";
//	}
	void m() & {
		std::cout << "m() &\n";
	}
	void m() const & {
		std::cout << "m() const &\n";
	}
	void m() && {
		std::cout << "m() &&\n";
	}
};



int main(int argc, char **argv) {
	S s{};
	s.m();

	S const sc{};
	sc.m();

	S{}.m();

	std::move(s).m();
}
