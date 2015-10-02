#include <iostream>
#include <vector>
#include <iomanip>
#include <iterator>
#include <algorithm>
int main(){
	std::vector<unsigned> v(20);
	iota(begin(v),end(v),1);
	std::ostream_iterator<int> out{std::cout,""};
	for_each(cbegin(v),cend(v),[=](unsigned row){
		transform(cbegin(v),cend(v),out,
				[=](unsigned col){
					std::cout.width(4); // nasty side effect on global...
					return col*row;
				});
		std::cout << '\n';
	});
}
