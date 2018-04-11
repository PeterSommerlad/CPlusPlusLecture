#include <array>

#include <iostream>

template<typename Container>
decltype(auto) extractMiddleElement(Container & container) {
  typename Container::value_type nthElement{};
  std::swap(container.at(container.size() / 2), nthElement);
  return nthElement;
}


int main(int argc, char **argv) {
	std::array<int, 3> values { 1, 2, 3 };
	std::cout << "Middle Element: " << extractMiddleElement(values) << '\n';
}
