#include <utility>
#include <iostream>
#include <string>

using namespace std::string_literals;

template<typename First, typename Second>
void printPair(std::ostream & out, std::pair<First, Second> const & p) {
	auto [f, s] = p;
	out << "first: " << f << " second: " << s;
}

int main() {
	std::pair p = std::make_pair(42, "answer"s);
	printPair(std::cout, p);
}

