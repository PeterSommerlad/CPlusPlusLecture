#include <iostream>
#include <iterator>
#include <algorithm>
struct intiterator
: std::iterator<std::input_iterator_tag,int>
{
	explicit intiterator(int start=0):value{start}{}
	bool operator==(intiterator const &r) const {
		return value == r.value;
	}
	bool operator!=(intiterator const &r) const {
		return !(*this == r);
	}
	value_type operator*() const { return value; }
	intiterator &operator ++() {
		++value;
		return *this;
	}
	intiterator operator ++(int) {
		auto old= *this;
		++(*this);
		return old;
	}
private:
	int value;
};

int main(){
	copy(intiterator{1},intiterator{11},
		 std::ostream_iterator<int>{std::cout,", "});
}



