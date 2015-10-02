#include <iterator>
#include <iostream>
#include <algorithm>
int main(){
	using in=std::istreambuf_iterator<char>;
	std::cout << count(in{std::cin},in{},'\n');
}


