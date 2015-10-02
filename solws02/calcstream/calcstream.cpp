#include "calcstream.h"
#include <istream>
#include "calc.h"

int calc(std::istream& in) {
	int l{};
	int r{};
	char op{};
	in >> l >> op >> r;
	return calc(l,r,op);
}
