#include "Ring5.h"
#include <ostream>

std::ostream& operator <<(std::ostream& out, const Ring5& r) {
	out << "Ring5{" << r.value() << '}';
	return out;
}
