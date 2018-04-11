#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <boost/operators.hpp>

struct IntInputterPtrBoost: boost::input_iterator_helper<IntInputterPtrBoost, int> {
	IntInputterPtrBoost() = default;
	explicit IntInputterPtrBoost(std::istream & in) :
			input { &in } {
	}
	IntInputterPtrBoost::value_type operator*();
	IntInputterPtrBoost & operator++() {
		return *this;
	}
	bool operator==(IntInputterPtrBoost const & other) const;
private:
	std::istream * input { };
};

IntInputterPtrBoost::value_type IntInputterPtrBoost::operator*() {
	value_type value { };
	if (input) {
		(*input) >> value;
	}
	return value;
}

bool IntInputterPtrBoost::operator==(IntInputterPtrBoost const & other) const {
	return (!input || !input->good()) && (!other.input || !other.input->good());
}

int main(int argc, char **argv) {
	std::istringstream input { "1 2 3" };
	std::copy(IntInputterPtrBoost { input }, IntInputterPtrBoost { }, std::ostream_iterator<int> { std::cout, "\n" });
}
