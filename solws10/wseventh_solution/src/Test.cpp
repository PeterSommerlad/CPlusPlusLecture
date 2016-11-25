#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "wseventh.h"

#include <sstream>

/*
 * Implement the wseventh function that takes an std::istream and an std::ostream. It counts how
 * often every word occurs and prints the seventh most frequent word (beware: not the seven most frequent words).
 * Use your word class from the previous exercises as it skips non-alphabet characters. You will need
 * to configure the dependency to your word class project (or copy the word files into this project)
 *
 * Add more tests below.
 *
 * This file contains two main() functions. One for running the tests, the other for running using
 * the wseventh() with the standard input.
 */



void test_wseventh_with_empty_input() {
	std::istringstream in{};
	std::ostringstream out{};

	wseventh(in, out);

	ASSERT_EQUAL("At least seven different words expected in input.\n", out.str());
}

void test_wseventh_with_six_input_words() {
	std::istringstream in{"A B C D E F A B C D E F A A"};
	std::ostringstream out{};

	wseventh(in, out);

	ASSERT_EQUAL("At least seven different words expected in input.\n", out.str());
}

void test_wseventh_with_seven_input_words() {
	std::istringstream in{"A B C D E F A B G C D E F F F"};
	std::ostringstream out{};

	wseventh(in, out);

	ASSERT_EQUAL("G\n", out.str());
}

void test_seventh_with_lorem_ipsum() {
	std::ifstream in{"test_resources/lorem_ipsum.txt"};
	std::ostringstream out{};

	wseventh(in, out);

	ASSERT_EQUAL("felis\n", out.str());
}

void test_seventh_with_chapter_six() {
	std::ifstream in{"test_resources/chapter_6.txt"};
	std::ostringstream out{};

	wseventh(in, out);

	ASSERT_EQUAL("is\n", out.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_wseventh_with_empty_input));
	s.push_back(CUTE(test_wseventh_with_six_input_words));
	s.push_back(CUTE(test_wseventh_with_seven_input_words));
	s.push_back(CUTE(test_seventh_with_lorem_ipsum));
	s.push_back(CUTE(test_seventh_with_chapter_six));
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
//	wseventh(std::cin, std::cout);
//}
