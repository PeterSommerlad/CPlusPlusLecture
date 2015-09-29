#include "overload.h"
namespace overload{
void incr(int& var, unsigned delta) {
	var += delta;
}
void incr(int& var) {
	++var;
}
}
