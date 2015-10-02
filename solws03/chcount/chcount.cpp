#include <iterator>
#include <iostream>
int main(){
	using in=std::istream_iterator<char>;
	std::cout << distance(in{std::cin},in{});
}


