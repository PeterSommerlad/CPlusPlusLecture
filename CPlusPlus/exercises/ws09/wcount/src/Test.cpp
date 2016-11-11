#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"


#include "wcount.h"
#include <sstream>

/*
 * Implement the wcount function that takes an std::istream and counts the words on that stream.
 * Use your word class from the previous exercises as it skips non-alphabet characters. You will need
 * to configure the dependency to your word class project (or copy the word files into this project)
 *
 * Add more tests below.
 *
 * This file contains two main() functions. One for running the tests, the other for running using
 * the wcount() with the standard input.
 */


void test_wcount_for_empty_input_is_0() {
	std::istringstream input{""};
	ASSERT_EQUAL(0, wcount(input));
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_wcount_for_empty_input_is_0));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}


int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}


//int main(int argc, char **argv) {
//	std::cout << wcount(std::cin);
//}
