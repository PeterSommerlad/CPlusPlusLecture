#include <utility>
#include <iostream>

struct S {
//	void operator&() const {
//		std::cout << "taking address of S\n";
//	}
};

S create() {
	return S{};
}

S & boiler(S & s) {
	return s;
}

int main(int argc, char **argv) {
	S s{};
	& s;

	S const cs{};
	& cs;

//	& S{}; // error: address of temporary

//	& create(); // error: address of temporary

	& boiler(s);

	std::addressof(s);

//	std::addressof(create()); // error: no matching overload for &&

	std::cout << "& s: " << &s << " and std::addressof(s): " << std::addressof(s) << std::endl;

}
