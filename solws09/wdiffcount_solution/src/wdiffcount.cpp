#include "wdiffcount.h"
#include "word.h"

#include <istream>
#include <iterator>
#include <set>

unsigned wdiffcount(std::istream& in) {
	using word_iterator = std::istream_iterator<word::Word>;
	std::set<word::Word> words{word_iterator{in}, word_iterator{}};
	return words.size();
}
