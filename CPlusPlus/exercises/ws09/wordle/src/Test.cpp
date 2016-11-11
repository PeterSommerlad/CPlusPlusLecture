#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "wordle.h"
#include <sstream>

/*
 * Implement the wordle function that takes an std::istream and an std::ostream. It counts how
 * often every word occurs in the input and prints the words with the count in "wordle" format
 * (See http://www.wordle.net/advanced for examples). It shall furthermore skip stop words.
 *
 * Stop words are provided in the file stop_words/english.stop. You can load it into your program
 * using an std::ifstream. You have to specify the files with an absolute or relative (to executable) path.
 *
 * Use your word class from the previous exercises as it skips non-alphabet characters. You will need
 * to configure the dependency to your word class project (or copy the word files into this project)
 *
 * Add more tests below.
 *
 * This file contains two main() functions. One for running the tests, the other for running using
 * the wordle() with the standard input.
 */


void test_wordle_for_empty_input_has_no_output() {
	std::istringstream input{""};
	std::ostringstream output{};
	wordle(input, output);
	ASSERT_EQUAL("", output.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_wordle_for_empty_input_has_no_output));
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
//	wordle(std::cin, std::cout);
//}
