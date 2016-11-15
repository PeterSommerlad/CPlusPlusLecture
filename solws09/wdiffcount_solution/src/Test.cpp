#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "wdiffcount.h"
#include <sstream>

/*
 * Implement the wdiffcount function that takes an std::istream and counts the different words on that stream.
 * Use your word class from the previous exercises as it skips non-alphabet characters. You will need
 * to configure the dependency to your word class project (or copy the word files into this project)
 *
 * Add more tests below.
 *
 * This file contains two main() functions. One for running the tests, the other for running using
 * the wdiffcount() with the standard input.
 */


void test_wdiffcount_for_empty_input_is_0() {
	std::istringstream input{""};
	ASSERT_EQUAL(0, wdiffcount(input));
}

void test_wdiffcount_for_different_words() {
	std::istringstream input{"This function has to count only different words"};
	ASSERT_EQUAL(8, wdiffcount(input));
}

void test_wdiffcount_for_recurring_words() {
	std::istringstream input{"It is true for all that that that that that that that refers to is not the same that that that that refers to!"};
	ASSERT_EQUAL(11, wdiffcount(input));
}

void test_wdiffcount_for_recurring_words_with_different_cases() {
	std::istringstream input{"Wenn Robben hinter Robben robben, robben Robben Robben nach."};
	ASSERT_EQUAL(4, wdiffcount(input));
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_wdiffcount_for_empty_input_is_0));
	s.push_back(CUTE(test_wdiffcount_for_different_words));
	s.push_back(CUTE(test_wdiffcount_for_recurring_words));
	s.push_back(CUTE(test_wdiffcount_for_recurring_words_with_different_cases));
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
//	std::cout << wdiffcount(std::cin);
//}
