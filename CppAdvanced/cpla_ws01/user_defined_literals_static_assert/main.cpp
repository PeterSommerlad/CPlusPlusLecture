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

namespace _impl {
template<char ...Digits>
struct parse_ternary;

constexpr unsigned long long three_to(std::size_t power) {
	return power ? 3ull * three_to(power - 1) : 1ull;
}

constexpr bool is_ternary_digit(char c) {
	return c == '0' || c == '1' || c == '2';
}

constexpr unsigned value_of(char c) {
	return c - '0';
}


template<char D, char ...Digits>
struct parse_ternary<D, Digits...> {
	static_assert(is_ternary_digit(D), "Digits of ternary must be 0, 1 or 2");
	static unsigned long long const value { value_of(D) * three_to(sizeof ...(Digits)) + parse_ternary<Digits...>::value };
};

template<>
struct parse_ternary<> {
	static unsigned	long long const value { 0 };
};
}

template<char ...Digits>
constexpr unsigned long long operator"" _ternary() {
	return _impl::parse_ternary<Digits...>::value;
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
	std::cout << "11_ternary is " << 11_ternary << '\n';
	std::cout << "02_ternary is " << 02_ternary << '\n';
	std::cout << "120_ternary is " << 120_ternary << '\n';
	//std::cout << "14_ternary is " << 14_ternary << '\n';//compile error:static_assert failed "Digits of ternary must be 0, 1 or 2"
}
