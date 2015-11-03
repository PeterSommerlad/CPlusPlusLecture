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
	std::rotate(begin(v),begin(v)+3,end(v));
	show(v, cout);
	std::reverse(begin(v),end(v));
	show(v, cout);
}
