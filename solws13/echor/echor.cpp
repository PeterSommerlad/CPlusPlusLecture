#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

int main(int argc, char const *argv[]) {
	std::vector<std::string> const v(argv + 1, argv + argc);
	copy(std::rbegin(v), std::rend(v), std::ostream_iterator<std::string> { std::cout, " " });
	std::cout << '\n';
	// without extra copying:
	copy(std::make_reverse_iterator(argv + argc), std::make_reverse_iterator(argv + 1),
			std::ostream_iterator<std::string> { std::cout, " " });
	std::cout << '\n';
}
