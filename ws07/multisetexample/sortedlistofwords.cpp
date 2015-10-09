#include <set>
#include <iostream>
#include <iterator>
int main(){
	using in=std::istream_iterator<std::string>;
	using out=std::ostream_iterator<std::string>;
	std::multiset<std::string> words{in{std::cin},in{}};
	copy(words.begin(),words.end(),out(std::cout,"\n"));
	auto bw=words.begin();
	while(bw!=words.end()){
		auto ew=words.upper_bound(*bw); // end of range
		copy(bw,ew,out{std::cout,", "});
		std::cout << '\n'; // next range on new line
		bw=ew;
	}
}
