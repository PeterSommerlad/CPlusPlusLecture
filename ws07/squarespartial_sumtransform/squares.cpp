#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
int main(){
	std::ostream_iterator<unsigned> out{std::cout,", "};
	std::vector<unsigned> v(10,1);
	copy(v.begin(),v.end(),out); std::cout << '\n';
	transform(v.begin(),v.end()-1,v.begin()+1,v.begin()+1, std::plus<unsigned>{});

	//partial_sum(v.begin(),v.end(),v.begin());
	copy(v.begin(),v.end(),out); std::cout << '\n';
	transform(v.begin(),v.end(),v.begin(),out,
			std::multiplies<unsigned>{});
}
