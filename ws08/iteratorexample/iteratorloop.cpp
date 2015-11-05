#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
int main(){
	std::vector<int> v{3,1,4,1,5,9,2,6};
	for(auto it=cbegin(v); it != cend(v) ; ++it){
		std::cout << *it << " is "
				  << ((*it%2)?"odd":"even") <<'\n';
	}
	// algorithm version of above loop:
	transform(cbegin(v),cend(v),
			 std::ostream_iterator<std::string>{std::cout,"\n"},
			 [](int i){return std::to_string(i) +" is "+((i%2)?"odd":"even");});

	for (std::vector<int>::const_reverse_iterator
			rit=crbegin(v); rit != crend(v); ++rit){
		std::cout << *rit << ", ";
	}
	// algorithm version of above loop:
	std::ostream_iterator<int> out{std::cout,", "};
	copy(crbegin(v),crend(v),out);
}

