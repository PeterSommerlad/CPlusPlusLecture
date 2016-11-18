#include "wcount.h"
#include "word.h"

#include <istream>
#include <iterator>

unsigned wcount(std::istream& in) {
	using word_iterator = std::istream_iterator<word::Word>;
	return std::distance(word_iterator{in}, word_iterator{});
}
