#include <vector>
#include <iostream>
int main(){
	std::vector<int> v{3,1,4,1,5,9,2,6};
	for(auto it=cbegin(v); it != cend(v) ; ++it){
		std::cout << *it << " is "
				  << ((*it%2)?"odd":"even") <<'\n';
	}
	for (std::vector<int>::const_reverse_iterator
			rit=crbegin(v); rit != crend(v); ++rit){
		std::cout << *rit << ", ";
	}
}

