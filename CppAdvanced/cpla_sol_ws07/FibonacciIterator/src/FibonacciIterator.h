#ifndef SRC_FIBONACCIITERATOR_H_
#define SRC_FIBONACCIITERATOR_H_

#include <iterator>
#include <cstddef>

struct FibonacciIterator {
	
	using iterator_category = std::input_iterator_tag;
	using value_type = int;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type *;
	using reference = value_type &;
	
	FibonacciIterator(int pos = 0) {
		while (pos-- > 0) {
			++*this;
		}
	}
	FibonacciIterator operator++(int) {
		auto const old = *this;
		++*this;
		return old;
	}

	FibonacciIterator& operator++() {
		auto const newval = f_1 + f_2;
		f_1 = f_2;
		f_2 = newval;
		return *this;
	}
	bool operator==(FibonacciIterator const &rhs) const {
		return f_1 == rhs.f_1 && f_2 == rhs.f_2;
	}
	bool operator !=(FibonacciIterator const &rhs) const {
		return !(*this == rhs);
	}
	value_type operator*() const {
		return f_1;
	}

private:
	value_type f_1{0};
	value_type f_2{1};
};

#endif /* SRC_FIBONACCIITERATOR_H_ */
