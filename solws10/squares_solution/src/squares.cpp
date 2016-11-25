#include "squares.h"

#include <vector>
#include <iterator>
#include <numeric>
#include <functional>
#include <algorithm>

std::vector<int> fill_with_squares() {
	std::vector<int> squares(10, 1);
	
	std::partial_sum(std::begin(squares), std::end(squares), std::begin(squares));
	std::transform(std::begin(squares), std::end(squares), std::begin(squares), std::begin(squares), std::multiplies<>{});
	
	return squares;
}
