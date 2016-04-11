#include<string>
#include<cstring>
#include<stdexcept>
#include<iostream>

namespace ternary {
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

template<char ...Digits>
struct parse_ternary<'0', Digits...> {
  static unsigned long long const value { parse_ternary<Digits...>::value };
};

template<char ...Digits>
struct parse_ternary<'1', Digits...> {
  static unsigned long long const value {
    1 * three_to(sizeof ...(Digits)) + parse_ternary<Digits...>::value };
};

template<char ...Digits>
struct parse_ternary<'2', Digits...> {
  static unsigned long long const value {
    2 * three_to(sizeof ...(Digits)) + parse_ternary<Digits...>::value };
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
	std::cout << "11_ternary is " << 11_ternary << '\n';
	std::cout << "02_ternary is " << 02_ternary << '\n';
	std::cout << "120_ternary is " << 120_ternary << '\n';
//	std::cout << "14_ternary is " << 14_ternary << '\n'; // compile-error
}
