#include "templatewithstaticmember.h"

int foo(){
	using dummytype=staticmember<int>;
	dummytype::dummy=42;
	return dummytype::dummy;
}
