#include "word.h" //use your word.h Header
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>

struct LengthComparator {
	bool operator()(word::Word const & lhs, word::Word const & rhs) const {
		if (lhs.size() < rhs.size()) { //Requires possibility to query size() of Word. Add that if necessary
			return true;
		}
		return lhs.size() == rhs.size() && lhs < rhs;
	}
};

int main(){
	using in = std::istream_iterator<word::Word>;
	
	std::set<word::Word, LengthComparator> wlist{in{std::cin}, in{}};
	copy(begin(wlist),end(wlist),
		 std::ostream_iterator<word::Word>{std::cout, "\n"});

}



