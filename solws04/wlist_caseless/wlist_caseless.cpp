#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

bool caseless_less(std::string const &l, std::string const &r){
	return lexicographical_compare(begin(l),end(l),begin(r),end(r),
			[](char lc, char rc){
				return std::tolower(lc)<std::tolower(rc);
			});
}

bool caseless_equal(std::string const &l, std::string const &r){
	return equal(begin(l),end(l),begin(r),end(r),
			[](char lc, char rc){
				return std::tolower(lc)==std::tolower(rc);
			});
}

int main(){
	using in=std::istream_iterator<std::string>;
	std::vector<std::string> wlist{in{std::cin},in{}};
	std::sort(begin(wlist),end(wlist),caseless_less);
	wlist.erase(unique(begin(wlist),end(wlist),caseless_equal),wlist.end());
	copy(begin(wlist),end(wlist),
		 std::ostream_iterator<std::string>{std::cout,"\n"});
}



