#include <iterator>
#include <iostream>
#include <algorithm>
int main(){
	using in=std::istream_iterator<char>;
	std::cout << count(in{std::cin},in{},'a');
}


