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

void test_wfavorite_for_fliegen() {
	std::istringstream input{"Wenn Fliegen hinter Fliegen fliegen, fliegen Fliegen Fliegen nach!"};
	std::ostringstream output{};
	wfavorite(input, output);
	ASSERT_EQUAL("Fliegen:6\n"
				 "hinter:1\n"
				 "nach:1\n"
			 	 "Wenn:1\n", output.str());
}

void test_lorem_ipsum() {
	std::ifstream input{"test_resources/lorem_ipsum.txt"};
	std::ostringstream output{};
	wfavorite(input, output);
	ASSERT_EQUAL("vitae:11\n"
				 "Ut:9\n"
				 "sed:8\n"
				 "augue:7\n"
				 "quis:7\n"
				 "urna:7\n"
				 "felis:6\n"
				 "id:6\n"
				 "nunc:6\n"
				 "tincidunt:6\n"
				 "vel:6\n"
				 "a:5\n"
				 "Etiam:5\n"
				 "hendrerit:5\n"
				 "In:5\n"
				 "nisi:5\n"
				 "Phasellus:5\n"
				 "turpis:5\n"
				 "ac:4\n"
				 "amet:4\n", output.str());
}

void test_chapter_six() {
	std::ifstream input{"test_resources/chapter_6.txt"};
	std::ostringstream output{};
	wfavorite(input, output);
	ASSERT_EQUAL("the:334\n"
				 "a:226\n"
				 "to:161\n"
				 "of:115\n"
				 "iterator:104\n"
				 "and:101\n"
				 "is:93\n"
				 "std:91\n"
				 "that:89\n"
				 "in:88\n"
				 "can:85\n"
				 "function:84\n"
				 "For:73\n"
				 "as:68\n"
				 "value:66\n"
				 "be:65\n"
				 "type:65\n"
				 "operator:63\n"
				 "With:62\n"
				 "return:54\n", output.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_wfavorite_for_empty_input_has_no_output));
	s.push_back(CUTE(test_wfavorite_for_fliegen));
	s.push_back(CUTE(test_lorem_ipsum));
	s.push_back(CUTE(test_chapter_six));
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
