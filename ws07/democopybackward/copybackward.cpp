#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
void show(std::vector<int> const &v, std::ostream& os) {
	std::ostream_iterator<int> out(os,", ");
	copy(cbegin(v), cend(v), out);
	os << '\n';
}
int main(){
	std::vector<int> v{3,1,4,1,5,9,2,6};
	using std::cout;
	show(v, cout);
	std::copy(cbegin(v)+2,cend(v),begin(v));
	show(v, cout);
	std::copy_backward(cbegin(v),cend(v)-2,end(v));
	show(v,cout);
	auto middle=begin(v)+(v.size()/2);
	std::swap_ranges(begin(v),middle,middle);
	show(v,cout);
}
