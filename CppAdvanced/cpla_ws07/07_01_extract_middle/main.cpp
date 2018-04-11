#include <array>
#include <iostream>
#include <boost/type_index.hpp>

template<template<typename, unsigned> class Container, typename Target, unsigned N>
Target extractMiddleElement(Container<Target, N> & container) {
	Target nthElement { };
	std::swap(container.at(N / 2), nthElement);

	{
		std::cout << "Type of Container => " << boost::typeindex::type_id<decltype(container)>().pretty_name() << '\n';
		std::cout << "Type of Target\t  => " << boost::typeindex::type_id<Target>().pretty_name() << '\n';
		std::cout << "Value of N\t  => " << N << '\n';
	}

	return nthElement;
}

int main(int argc, char **argv) {
	std::array<int, 3> values { 1, 2, 3 };
	std::cout << "Middle Element: " << extractMiddleElement(values) << '\n';
}

