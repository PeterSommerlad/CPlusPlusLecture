#include <iostream>

void default_specification() {
}

void function() noexcept {
}

////Cannot overload on noexcept
//void function() {
//}

template<bool NoException>
void function(int) noexcept(NoException) {
}

int main() {
	std::cout << std::boolalpha;
	std::cout << "is default_specification() noexcept? " << noexcept (default_specification()) << '\n';
	std::cout << "is function() noexcept? " << noexcept (function()) << '\n';
	std::cout << "is function<true>(int) noexcept? " << noexcept (function<true>(1)) << '\n';
	std::cout << "is function<false>() noexcept? " << noexcept (function<false>(1)) << '\n';
}

