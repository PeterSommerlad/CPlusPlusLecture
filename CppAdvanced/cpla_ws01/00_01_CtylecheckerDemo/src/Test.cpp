#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <set>
#include <iostream>
#include <vector>

#include "header.h"

void foo() {
	std::vector<int> const i;
}


void testIncrementViaReturnValue() {
	ASSERTM("start writing tests", false);
	ASSERTM("Only one ASSERT per test", true);
}

void testTuplesAreDifferent() {
	int const a { 1 };
	int const b { 2 };
	int const c { 3 };
	ASSERT_EQUAL(std::tie(a, b, c), std::tie(b, c, a));
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testIncrementViaReturnValue));
	s.push_back(CUTE(testTuplesAreDifferent));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
