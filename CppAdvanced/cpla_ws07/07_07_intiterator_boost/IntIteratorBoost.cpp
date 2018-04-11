#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/operators.hpp>

struct IntIteratorBoost: boost::input_iterator_helper<IntIteratorBoost, int> {
	explicit IntIteratorBoost(int start = 0) :
			value { start } {
	}
	bool operator==(IntIteratorBoost const &r) const {
		return value == r.value;
	}
	value_type operator*() const {
		return value;
	}
	IntIteratorBoost &operator ++() {
		++value;
		return *this;
	}
private:
	int value;
};

int main() {
	copy(IntIteratorBoost { 1 }, IntIteratorBoost { 11 }, std::ostream_iterator<int> { std::cout, ", " });
}
