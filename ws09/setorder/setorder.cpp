#include <set>
#include <functional>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <iostream>



struct caseless{
	using string=std::string;
	bool operator()(string const &l, string const &r){
		return std::lexicographical_compare(
				l.begin(),l.end(),r.begin(),r.end(),
				[](char l,char r){
			return std::tolower(l) < std::tolower(r);
		});
	}
};









int main(){
	std::set<int,std::greater<int>> reverse_int_set{};









	using std::string;
	using caseless_set=std::multiset<string,caseless>;
	using in=std::istream_iterator<string>;
	caseless_set wlist{in{std::cin},in{}};
	std::ostream_iterator<string> out{std::cout,"\n"};
	copy(wlist.begin(),wlist.end(),out);
}
