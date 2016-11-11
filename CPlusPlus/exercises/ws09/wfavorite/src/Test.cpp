#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "wfavorite.h"
#include <sstream>

/*
 * Implement the wfavorite function that takes an std::istream and an std::ostream. It counts how
 * often every word occurs in the input and prints the top 20 words to the output.
 * Use your word class from the previous exercises as it skips non-alphabet characters. You will need
 * to configure the dependency to your word class project (or copy the word files into this project)
 *
 * Add more tests below.
 *
 * This file contains two main() functions. One for running the tests, the other for running using
 * the wfavorite() with the standard input.
 */


void test_wfavorite_for_empty_input_has_no_output() {
	std::istringstream input{""};
	std::ostringstream output{};
	wfavorite(input, output);
	ASSERT_EQUAL("", output.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_wfavorite_for_empty_input_has_no_output));
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
//	wfavorite(std::cin, std::cout);
//}
