#include "wseventh.h"
#include "word.h"

#include <istream>
#include <ostream>
#include <iterator>
#include <algorithm>
#include <map>
#include <tuple>
#include <vector>

unsigned constexpr NTH = 7;
unsigned constexpr NTH_INDEX = NTH - 1;

using word_input_iterator = std::istream_iterator<word::Word>;
using words_with_count = std::map<word::Word, unsigned>;
using count_word_pair = std::pair<unsigned, word::Word>;
using words = std::vector<count_word_pair>;

//Descending occurrence but ascending alphabetical order of words
struct count_word_pair_comparator {
	bool operator()(count_word_pair const & lhs, count_word_pair const & rhs) const {
		return std::tie(rhs.first, lhs.second) < std::tie(lhs.first, rhs.second);
	}
};

words_with_count count_words(std::istream & in) {
	words_with_count word_occurrences{};
	std::for_each(
			word_input_iterator{in},
			word_input_iterator{},
			[&word_occurrences](word::Word const & word) {
				word_occurrences[word]++;
			});
	return word_occurrences;
}

word::Word nth_word(words_with_count const & counts, unsigned n_index) {
	words all_words{};
	std::transform(
			std::begin(counts),
			std::end(counts),
			std::inserter(all_words, std::begin(all_words)),
			[](auto const & word_occurrence) { //std::map<word::Word, unsigned>::value_type
				return std::make_pair(word_occurrence.second, word_occurrence.first); //Bug in CDT: Parameter types of generic lambdas are not recognized yet
			});
	std::nth_element(
			std::begin(all_words),
			std::begin(all_words) + n_index,
			std::end(all_words),
			count_word_pair_comparator{});
	return all_words[n_index].second;
}

void wseventh(std::istream & in, std::ostream & out) {
	auto word_count = count_words(in);
	if (word_count.size() < NTH) {
		out << "At least seven different words expected in input.\n";
		return;
	}
	out << nth_word(word_count, NTH_INDEX) << '\n';
}
