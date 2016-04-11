#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/operators.hpp>
struct intiteratorboost
: boost::input_iterator_helper<intiteratorboost,int>
{
	explicit intiteratorboost(int start=0):value{start}{}
	bool operator==(intiteratorboost const &r) const {
		return value == r.value;
	}
	value_type operator*() const { return value; }
	intiteratorboost &operator ++() {
		++value;
		return *this;
	}
private:
	int value;
};

int main(){
	copy(intiteratorboost{1},intiteratorboost{11},
		 std::ostream_iterator<int>{std::cout,", "});
}
