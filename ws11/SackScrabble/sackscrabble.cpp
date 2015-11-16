#include <iostream>
#include "Sack.h"
#include <iterator>

int main(){
	Sack<char> scrabble{};
	for (char c='A'; c <= 'Z'; ++c)
		scrabble.putInto(c);
	std::vector<int> values{scrabble};
	copy(values.begin(),values.end(),std::ostream_iterator<int>{std::cout,"; "});
	std::cout << '\n';
	while (!scrabble.empty()){
		std::cout << "play letter: " << scrabble.getOut() << '\n';
	}
}
