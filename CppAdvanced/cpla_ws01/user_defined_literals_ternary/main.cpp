#include<string>
#include<cstring>
#include<stdexcept>
#include<iostream>

namespace ternary {
unsigned long long operator"" _3(char const *s) {
	size_t convertedupto { };
	auto res = std::stoull(s, &convertedupto, 3u);
	if (convertedupto != strlen(s))
		throw std::logic_error { "invalid ternary" };
	return res;
}
}

int main(int argc, char **argv) {
	using namespace ternary;
	int four = 11_3;
	std::cout << "four is " << four << '\n';
	try {
		four = 14_3; // throws
	} catch (std::exception const &e) {
		std::cout << e.what() << '\n';
	}
}

