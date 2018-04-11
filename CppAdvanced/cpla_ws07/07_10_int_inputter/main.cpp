#include <iterator>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cstddef>

struct IntInputter {

	using iterator_category = std::input_iterator_tag;
	using value_type = int;
	using difference_type = std::ptrdiff_t;
	using pointer = int *;
	using reference = int &;

	IntInputter();
	explicit IntInputter(std::istream & in) :
			input { in } {}
	value_type operator*();
	IntInputter & operator++() {
		return *this;
	}
	IntInputter operator++(int) {
		IntInputter old { *this };
		++(*this);
		return old;
	}
	bool operator==(IntInputter const & other) const;
	bool operator!=(IntInputter const & other) const {
		return !(*this == other);
	}
private:
	std::istream & input;
};

namespace {
  // a global helper needed...
  std::istringstream empty{};
}

IntInputter::IntInputter() : input { empty } {
  // guarantee the empty stream is not good()
  input.clear(std::ios_base::eofbit);
}

IntInputter::value_type IntInputter::operator*() {
  value_type value{};
  input >> value;
  return value;
}

bool IntInputter::operator==(const IntInputter & other) const {
	return !input.good() && !other.input.good();
}


int main(int argc, char **argv) {
	std::istringstream input{"1 2 3"};
	std::copy(IntInputter{input}, IntInputter{}, std::ostream_iterator<int>{std::cout, "\n"});
}
