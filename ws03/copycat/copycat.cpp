#include <iterator>
#include <iostream>
#include <algorithm>
int main(){
	using input=std::istreambuf_iterator<char>;
	input eof{};
	input in{std::cin};
	std::ostream_iterator<char> out{std::cout};
	copy(in,eof,out);
}
