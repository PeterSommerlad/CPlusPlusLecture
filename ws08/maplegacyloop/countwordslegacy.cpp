#include <map>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/iterator/transform_iterator.hpp>
#include <functional>
template<typename K, typename V>
struct key: std::unary_function<std::pair<K, V>const &, K> {
	K const &operator()(std::pair<K, V>const &p) const {
		return p.first;
	}
};
template<typename K, typename V>
struct value: std::unary_function<std::pair<K, V>const &, V> {
	V const &operator()(std::pair<K, V>const &p) const {
		return p.second;
	}
};

int main() {
	typedef std::map<std::string, int> wordmap;
	using std::placeholders::_1;
	wordmap words;
	std::string s;
	while (bool(std::cin >> s) && s != ".")
		++words[s];
	std::cout << "done reading"<< std::endl;

	typedef wordmap::const_iterator iter;
	for (iter it = begin(words); it != end(words); ++it)
		std::cout << it->first << " = " << it->second << '\n';
	std::cout << "done first"<< std::endl;
	key<wordmap::key_type, wordmap::mapped_type> const selKey { };
	std::ostream_iterator<std::string> outstr{std::cout, ", "};
	transform(begin(words), end(words), outstr, selKey);
	std::cout << "\nwith transform_iterator and keys:\n";
	copy(boost::make_transform_iterator(begin(words), selKey),
		 boost::make_transform_iterator(end(words), selKey), outstr);
	std::cout << "\nwith transform and bind on first\n";
	transform(begin(words), end(words), outstr,
			std::bind(&wordmap::value_type::first, _1));
	std::cout << "\nwith transform_iterator and value\n";

	value<wordmap::key_type, wordmap::mapped_type> const selectVal { };
	copy(boost::make_transform_iterator(begin(words), selectVal),
		 boost::make_transform_iterator(end(words), selectVal),
			std::ostream_iterator<int>(std::cout, ", "));
	std::cout << "\n keys\n";
	auto selkey = std::bind(&wordmap::value_type::first, _1);
	copy(boost::make_transform_iterator(begin(words), selkey),
		 boost::make_transform_iterator(end(words), selkey), outstr);

	std::cout << std::endl;
}
