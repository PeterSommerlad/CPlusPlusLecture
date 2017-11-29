#ifndef MEDIAN_H_
#define MEDIAN_H_

#include <string>
#include <algorithm>

template<typename T>
T const &median(T const &a, T const &b, T const &c) {
	return std::max(std::min(a, b), std::min(std::max(a, b), c));
}

// overload for pointers, don't allow pointers
template<typename T>
T *median(T *a, T *b, T *c) = delete;

// overload for string literals
std::string median(char const *ap, char const *bp, char const *cp) {
	std::string a { ap };
	std::string b { bp };
	std::string c { cp };
	return median(a, b, c);
}

#endif /* MEDIAN_H_ */
