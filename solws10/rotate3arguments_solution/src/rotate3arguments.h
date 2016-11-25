#ifndef ROTATE3ARGUMENTS_H_
#define ROTATE3ARGUMENTS_H_

#include <utility>

template<typename T>
void rotate3arguments(T &a, T& b, T& c) {
	std::swap(a, b); // using swap avoids unnecessary copying and temporaries
	std::swap(b, c);
}

#endif /* ROTATE3ARGUMENTS_H_ */
