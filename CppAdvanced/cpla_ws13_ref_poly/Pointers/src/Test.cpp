#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <array>

namespace simplified {
template <typename T>
using observer_ptr=T *;
}


int demo(int *const pi){
	//*pi++;
	(*pi)++;
	return *pi;
}
void dont_demo(int *const pi){
	1[pi]=42;
	pi[0]=41;
}
void thisIsATest() {
	using simplified::observer_ptr;
	int i{42};

	observer_ptr<int> oi=&i;
	ASSERT_EQUAL(i,*oi);
}
void testDemo(){
	int i{42};
	int j=demo(&i);
	ASSERT_EQUAL(i,j);
}
void testDont(){
	std::array<int,2> a{};
	dont_demo(a.data());
	std::initializer_list<int> exp{41,42};
	ASSERT_EQUAL_RANGES(begin(exp),end(exp),begin(a),end(a));

}



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	s.push_back(CUTE(testDemo));
	s.push_back(CUTE(testDont));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
