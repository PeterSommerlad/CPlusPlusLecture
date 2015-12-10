#include <iostream>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <algorithm>
#include <iterator>
#include <functional>

struct is_prime{
	bool operator()(unsigned int val) const {
	if (val < 2) return false;
	using std::placeholders::_1;
	auto ce=boost::make_counting_iterator(val);
	return ce==std::find_if_not(boost::make_counting_iterator(2u),ce,
				[val](unsigned n){ return val % n; });
//					bind(std::modulus<unsigned>{},val,_1));
}
};
int main(){
	std::copy_n(boost::make_filter_iterator(is_prime{},boost::make_counting_iterator(1u)
	// if the following line is omitted we might have undefined behavior, because of uninitialized unsigned value
	//			,boost::make_counting_iterator(std::numeric_limits<unsigned>::max()) // must be different from above value
			),40,std::ostream_iterator<unsigned>{std::cout,", "});
}
