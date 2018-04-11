#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstddef>

struct IntIterator {

	using iterator_category = std::input_iterator_tag;
	using value_type = int;
	using difference_type = std::ptrdiff_t;
	using pointer = int *;
	using reference = int &;

	explicit IntIterator(int const start = 0) :
			value{start} {
	}

	bool operator==(IntIterator const & r) const {
		return value == r.value;
	}

	bool operator!=(IntIterator const & r) const {
		return !(*this == r);
	}

	value_type operator*() const {
		return value;
	}

	IntIterator & operator++() {
		++value;
		return *this;
	}

	IntIterator operator++(int) {
		auto old = *this;
		++(*this);
		return old;
	}

private:
	value_type value;
};

int main() {
	copy(IntIterator{1}, IntIterator{11}, std::ostream_iterator<int>{std::cout, ", "});
}

