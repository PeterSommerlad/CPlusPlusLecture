#include "Hello.h"
#include <ostream>
void Hello::sayHello(std::ostream& out) const {
	out << "Hello, world!\n";
}
