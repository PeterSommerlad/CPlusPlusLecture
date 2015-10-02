#include <iterator>
#include <iostream>
#include <numeric>
int main(){
	using in=std::istream_iterator<double>;
	std::cout << accumulate(in{std::cin},in{},0.0);
}


