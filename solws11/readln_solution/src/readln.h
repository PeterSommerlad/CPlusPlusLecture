#ifndef READLN_H_
#define READLN_H_

#include <istream>
#include <sstream>
#include <string>

namespace readln_impl {
template<typename ...I>
void doread(std::istream &in, I&...vars);

void doread(std::istream &in, std::string &rest) {
	getline(in, rest); // consume the rest of the line into rest
}

template<typename FIRST, typename ...I>
void doread(std::istream &in, FIRST &var, I&...vars) {
	in >> var;
	if (sizeof...(I)) doread(in,vars...);
}
}

template<typename ...I>
void readln(std::istream &in, I&...vars) {
	using namespace readln_impl;
	std::string line { };
	getline(in, line);
	std::istringstream input { line };
	doread(input, vars...);
	if (input.fail())
		in.setstate(std::ios::failbit);
}

#endif /* READLN_H_ */
