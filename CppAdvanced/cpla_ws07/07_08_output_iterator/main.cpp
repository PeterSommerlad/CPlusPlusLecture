#include <iostream>
#include <boost/operators.hpp>
#include <iterator>
#include <cstddef>

struct MyIntOutIter {

	using iterator_category = std::output_iterator_tag;
	using value_type = int;
	using difference_type = std::ptrdiff_t;
	using pointer = int *;
	using reference = int &;

	MyIntOutIter & operator++() {
		return *this;
	}
	MyIntOutIter operator++(int) {
		return *this;
	}
	MyIntOutIter const & operator*() const {
		return *this;
	}
	void operator=(value_type val) const {
		std::cout << "val = " << val << '\n';
	}

};

struct MyIntOutIterBoost: boost::output_iterator_helper<MyIntOutIterBoost> {
	void operator=(int val) const {
		std::cout << "value = " << val << '\n';
	}
};

int main(int argc, char **argv) {
	MyIntOutIter intOutIter { };
	*intOutIter++ = 5;

	MyIntOutIterBoost intOutIterBoost { };
	*intOutIterBoost++ = 5;

}
