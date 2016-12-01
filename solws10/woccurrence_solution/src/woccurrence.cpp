#include "woccurrence.h"
#include "word.h"

#include <istream>
#include <ostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>
#include <set>
#include <map>

using word_line = std::vector<word::Word>;

namespace word {

using word_iterator = std::istream_iterator<Word>;

std::istream & operator>>(std::istream & in, word_line & line) {
	std::string input_line{};
	if (std::getline(in, input_line)) {
		line.clear();
		std::istringstream line_stream{input_line};
		std::copy(word_iterator{line_stream}, word_iterator{}, std::back_inserter(line));
	}
	return in;
}

}

struct word_line_collector {
	void operator()(word_line const & line) {
		line_number++;
		std::for_each(std::begin(line), std::end(line), [this](word::Word const & w) {
			word_lines[w].insert(line_number);
		});
	}

	void print(std::ostream & out) const {
		std::for_each(
				std::begin(word_lines), std::end(word_lines),
				[&](auto const & word_line){
					out << word_line.first << " ";
					std::copy(
							std::begin(word_line.second), std::end(word_line.second),
							std::ostream_iterator<unsigned>{out, " "});
					out << '\n';
				});
	}
private:
	unsigned line_number{};
	std::map<word::Word, std::set<unsigned>> word_lines{};
};

std::ostream & operator <<(std::ostream & out, word_line_collector const & collector) {
	collector.print(out);
	return out;
}

void woccurrence(std::istream & in, std::ostream & out) {
	std::istream_iterator<word_line> line_iterator{in}, eof{};
	out << std::for_each(line_iterator, eof, word_line_collector{});
}