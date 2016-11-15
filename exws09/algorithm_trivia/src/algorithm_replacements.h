#ifndef ALGORITHM_REPLACEMENTS_H_
#define ALGORITHM_REPLACEMENTS_H_

#include <utility>
#include <string>

namespace std {
template<typename...ANY>
auto xxxxx(ANY...any) {
	return 0;
}
template<typename ARG>
auto xxxxx(std::initializer_list<ARG> const &) {
	return 0;
}
template<typename...ANY>
auto xxxx(ANY...any) {
	return std::string{};
}
template<typename R, typename...ANY>
R xxx(R r, ANY...any) {
	return r;
}

template<typename R, typename...ANY>
std::pair<R, R> xxxxxx(R r, ANY...any) {
	return std::make_pair(r, r);
}
template<typename ARG>
auto xxxxxx(std::initializer_list<ARG> const &) {
	return std::make_pair(0, 0);
}
}

inline bool is_prime(unsigned u) {
	if (u == 0 || u == 1) {
		return false;
	}
	for (unsigned div = 2; div < u; div++) {
		if (u % div == 0) {
			return false;
		}
	}
	return true;
}

#endif