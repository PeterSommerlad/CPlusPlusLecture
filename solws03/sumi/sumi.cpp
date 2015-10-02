#include <iterator>
#include <iostream>
#include <numeric>
int main(){
	using in=std::istream_iterator<int>;
	std::cout << accumulate(in{std::cin},in{},0);
}


