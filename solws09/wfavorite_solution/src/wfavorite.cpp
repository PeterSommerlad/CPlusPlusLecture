#include "wfavorite.h"
#include "word.h"

#include <istream>
#include <ostream>
#include <iterator>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#include <tuple>


unsigned constexpr LIMIT { 20 };

using word_input_iterator = std::istream_iterator<word::Word>;
using words_with_count = std::map<word::Word, unsigned>;
using count_word_pair = std::pair<unsigned, word::Word>;

//Descending occurrence but ascending alphabetical order of words
struct count_word_pair_comparator {
	bool operator()(count_word_pair const & lhs, count_word_pair const & rhs) const {
		return std::tie(rhs.first, lhs.second) < std::tie(lhs.first, rhs.second);
	}
};

using words = std::set<count_word_pair, count_word_pair_comparator>;

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



words count_words_in(std::istream & in) {
	auto counts = count_words(in);
	words all_words{};
	std::transform(
			std::begin(counts),
			std::end(counts),
			std::inserter(all_words, std::begin(all_words)),
			[](auto const & word_occurrence) { //std::map<word::Word, unsigned>::value_type
				return std::make_pair(word_occurrence.second, word_occurrence.first); //Bug in CDT: Parameter types of generic lambdas are not recognized yet
			});
	return all_words;
}

namespace word {

std::ostream & operator<<(std::ostream & out, words::value_type const & count_word) {
	out << count_word.second << ":" << count_word.first;
	return out;
}

}

void print_favorite_words(std::ostream& out, words const & all_words, unsigned long long limit) {
	auto nof_words = all_words.size();
	auto nof_displayed_elements = std::min(limit, nof_words);
	auto end = std::next(std::begin(all_words), nof_displayed_elements);
	std::copy(
			std::begin(all_words),
			end,
			std::ostream_iterator<words::value_type>{out, "\n"});
}

void wfavorite(std::istream & in, std::ostream & out) {
	auto count_sorted_words = count_words_in(in);
	print_favorite_words(out, count_sorted_words, LIMIT);
}