#include <algorithm>
#include <set>
#include <iterator>
#include <iostream>
using mset=std::multiset<int>;
using oi=std::ostream_iterator<mset::value_type>;
void show(mset const &s,std::ostream& os){
	copy(begin(s),end(s),oi{os,", "});
	os << '\n';
}
int main(){
	using std::cout;
	mset a{3,1,4,1};
	mset b{4,1,5,9};
	show(a,cout);
	show(b,cout);
	set_difference(begin(a),end(a),
		 begin(b),end(b),oi{cout,", "}); cout << '\n';
	set_intersection(begin(a),end(a),
			 begin(b),end(b),oi{cout,", "}); cout << '\n';
	set_symmetric_difference(begin(a),end(a),
			 begin(b),end(b),oi{cout,", "}); cout << '\n';
	set_union(begin(a),end(a),
			 begin(b),end(b),oi{cout,", "}); cout << '\n';
	merge(begin(a),end(a),
			 begin(b),end(b),oi{cout,", "}); cout << '\n';
}
