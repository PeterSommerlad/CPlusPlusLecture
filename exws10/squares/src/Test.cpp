#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <vector>


void test_fill_with_squares() {
	std::vector<int> const expected{1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
	ASSERT_EQUAL(expected, expected);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(test_fill_with_squares));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
