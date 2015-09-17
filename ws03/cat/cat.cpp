#include <iterator>
#include <iostream>
#include <algorithm>
#include <string>
int main(){
	using input=std::istream_iterator<std::string>;
	input eof{};
	input in{std::cin};
	std::ostream_iterator<std::string> out{std::cout," "};
	copy(in,eof,out);
}
