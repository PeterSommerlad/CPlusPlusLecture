#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>
bool isPalindrome(std::string const &s){
	return equal(s.begin(),s.end(),s.rbegin(),
			[](char l, char r){
				return std::tolower(l)==std::tolower(r);
			});
}

int main(){
	std::ifstream input{"/usr/share/dict/words"};
	using initer=std::istream_iterator<std::string>;
	std::ostream_iterator<std::string> out{std::cout,"\n"};
	copy_if(initer{input},initer{},out,isPalindrome);
}
