#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

void show(std::vector<int> const &v, std::ostream& os) {
	std::ostream_iterator<int> out(os,", ");
	copy(cbegin(v), cend(v), out);
	os << std::boolalpha << "is " <<
			(is_heap(cbegin(v),cend(v))?"a":"no")
			<< " heap.\n";
}

int main(){
	std::vector<int> v{3,1,4,1,5,9,2,6};
	using std::cout;                 show(v, cout);
	std::make_heap(begin(v),end(v)); show(v, cout);
	std::pop_heap(begin(v),end(v));  show(v, cout);
	v.pop_back();                    show(v, cout);
	v.push_back(8);	                 show(v,cout);
	std::push_heap(begin(v),end(v)); show(v,cout);
	std::sort_heap(begin(v),end(v)); show(v,cout);
}
