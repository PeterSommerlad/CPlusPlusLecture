#include "MyMin.h"
#include <string>
namespace MyMin {

const char* min(const char* a, const char* b) {
	return std::string(a)<std::string(b)?a:b;
}

}
