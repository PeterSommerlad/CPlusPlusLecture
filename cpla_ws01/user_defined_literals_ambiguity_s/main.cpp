#include<string>
#include<chrono>
#include<iostream>
#include<typeinfo>

int main(int argc, char **argv) {
	using namespace std::string_literals;
	using namespace std::chrono_literals;
	auto one_s = 1s;
	auto one_point_zero_s = 1.0s;
	auto fourty_two_s = "42"s;
	std::cout << typeid(one_s).name() << '\n';
	std::cout << typeid(one_point_zero_s).name() << '\n';
	std::cout << typeid(fourty_two_s).name() << '\n';
}
