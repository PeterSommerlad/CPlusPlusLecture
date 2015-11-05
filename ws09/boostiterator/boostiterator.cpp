#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

struct odd{
	bool operator()(int n)const{return n%2;}
};
int main(){
	using counter=boost::counting_iterator<int>;
	std::vector<int> v(counter { 1 }, counter { 11 });
	std::ostream_iterator<int> out{std::cout,", "};
	copy(v.begin(),v.end(),out);
	std::cout << '\n';
	using boost::make_filter_iterator;
	copy(make_filter_iterator(odd{},v.begin(),v.end()),
		 make_filter_iterator(odd{},v.end(),v.end()),
		 out);
	std::cout << '\n';
	using boost::make_transform_iterator;
	auto square=[](auto x){ return x*x;};
	copy(make_transform_iterator(v.begin(),square),
		 make_transform_iterator(v.end(),square),
         out);
}
