#include "word.h" //use your word.h Header
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>

int main(){
	using in = std::istream_iterator<word::Word>;
	
	std::set<word::Word, std::greater<>> wlist{in{std::cin}, in{}};
	copy(begin(wlist),end(wlist),
		 std::ostream_iterator<word::Word>{std::cout, "\n"});

}



