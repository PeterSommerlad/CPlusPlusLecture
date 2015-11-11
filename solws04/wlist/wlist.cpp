#include <iostream>
#include <string>
#include <iterator>
#include <set>
#include <algorithm>

int main(){
	using in=std::istream_iterator<std::string>;
	std::set<std::string> wlist{in{std::cin},in{}};
	copy(begin(wlist),end(wlist),
		 std::ostream_iterator<std::string>{std::cout,"\n"});

}



