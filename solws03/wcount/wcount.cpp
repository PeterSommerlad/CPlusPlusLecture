#include <iterator>
#include <iostream>
#include <string>
int main(){
	using in=std::istream_iterator<std::string>;
	std::cout << distance(in{std::cin},in{});
}


