#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "woccurrence.h"

#include <sstream>


/*
 * Implement the woccurrence function that takes an std::istream and an std::ostream. It records in which
 * lines of the input a word occurs.
 * Use your word class from the previous exercises as it skips non-alphabet characters. You will need
 * to configure the dependency to your word class project (or copy the word files into this project)
 *
 * Add more tests below.
 *
 * This file contains two main() functions. One for running the tests, the other for running using
 * the woccurrence() with the standard input.
 */


void test_woccurrence_with_empty_input() {
	std::istringstream in{};
	std::ostringstream out{};

	woccurrence(in, out);

	ASSERT_EQUAL("At least seven different words expected in input.\n", out.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_woccurrence_with_empty_input));
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
//	woccurrence(std::cin, std::cout);
//}
