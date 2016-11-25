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

	ASSERT_EQUAL("", out.str());
}

void test_woccurrence_with_one_input_word() {
	std::istringstream in{"Hello"};
	std::ostringstream out{};

	woccurrence(in, out);

	ASSERT_EQUAL("Hello 1 \n", out.str());
}

void test_woccurrence_with_two_input_words() {
	std::istringstream in{"Hello again"};
	std::ostringstream out{};

	woccurrence(in, out);

	ASSERT_EQUAL("again 1 \n"
				 "Hello 1 \n", out.str());
}

void test_wordoccurrence_with_one_word_on_multiple_lines() {
	std::istringstream in{"Hello\nHello\nHello"};
		std::ostringstream out{};

		woccurrence(in, out);

		ASSERT_EQUAL("Hello 1 2 3 \n", out.str());
}

void test_wordoccurrence_with_exercise_example_input() {
	std::istringstream in{"Hello\n"
						  "Hello again\n"
						  "Song by whom?"};
		std::ostringstream out{};

		woccurrence(in, out);

		ASSERT_EQUAL("again 2 \n"
					 "by 3 \n"
					 "Hello 1 2 \n"
					 "Song 3 \n"
					 "whom 3 \n", out.str());
}

void test_wordoccurrence_with_lorem_ipsum_input() {
	std::ifstream in{"test_resources/lorem_ipsum.txt"};
	std::ostringstream out{};

	woccurrence(in, out);

	ASSERT_EQUAL("a 3 5 7 9 \n"
				 "ac 1 3 5 7 \n"
				 "accumsan 3 5 7 \n"
				 "adipiscing 1 \n"
				 "Aenean 9 \n"
				 "Aliquam 1 7 \n"
				 "aliquet 5 7 \n"
				 "amet 1 3 5 \n"
				 "ante 9 \n"
				 "arcu 3 \n"
				 "at 1 3 7 \n"
				 "auctor 1 5 \n"
				 "augue 1 3 5 9 \n"
				 "blandit 5 9 \n"
				 "commodo 7 9 \n"
				 "condimentum 1 3 9 \n"
				 "consectetur 1 \n"
				 "consequat 1 9 \n"
				 "convallis 1 \n"
				 "Cras 3 5 9 \n"
				 "Curabitur 7 \n"
				 "cursus 7 9 \n"
				 "dapibus 1 7 \n"
				 "diam 1 \n"
				 "dictum 1 3 \n"
				 "dignissim 1 3 \n"
				 "dolor 1 7 \n"
				 "Donec 1 7 \n"
				 "dui 3 7 \n"
				 "Duis 1 \n"
				 "efficitur 3 9 \n"
				 "eget 5 7 \n"
				 "eleifend 1 7 \n"
				 "elementum 7 \n"
				 "elit 1 9 \n"
				 "enim 1 3 7 \n"
				 "erat 1 5 \n"
				 "eros 1 3 5 \n"
				 "est 1 3 \n"
				 "et 7 9 \n"
				 "Etiam 3 5 7 9 \n"
				 "eu 1 3 9 \n"
				 "euismod 3 7 \n"
				 "ex 7 \n"
				 "facilisis 7 \n"
				 "faucibus 1 5 \n"
				 "felis 3 7 9 \n"
				 "fermentum 3 7 \n"
				 "feugiat 7 \n"
				 "fringilla 9 \n"
				 "Fusce 3 7 9 \n"
				 "gravida 9 \n"
				 "hendrerit 1 3 7 \n"
				 "id 1 3 5 7 \n"
				 "imperdiet 1 \n"
				 "In 7 9 \n"
				 "interdum 3 5 9 \n"
				 "ipsum 1 \n"
				 "justo 3 5 7 \n"
				 "lacinia 3 9 \n"
				 "lacus 1 \n"
				 "laoreet 3 7 \n"
				 "lectus 9 \n"
				 "leo 1 3 5 \n"
				 "libero 3 9 \n"
				 "ligula 1 5 9 \n"
				 "lobortis 5 \n"
				 "Lorem 1 \n"
				 "luctus 3 9 \n"
				 "magna 1 7 \n"
				 "massa 5 7 \n"
				 "mauris 5 7 \n"
				 "metus 1 9 \n"
				 "mi 1 7 \n"
				 "molestie 9 \n"
				 "mollis 5 7 \n"
				 "Morbi 7 \n"
				 "Nam 5 \n"
				 "nec 1 7 \n"
				 "neque 7 \n"
				 "nibh 5 \n"
				 "nisi 1 3 7 \n"
				 "nisl 7 \n"
				 "non 1 7 \n"
				 "Nullam 5 7 9 \n"
				 "nunc 1 3 5 7 \n"
				 "odio 1 5 \n"
				 "orci 3 5 \n"
				 "ornare 1 9 \n"
				 "pharetra 3 \n"
				 "Phasellus 1 3 5 7 9 \n"
				 "placerat 7 \n"
				 "posuere 7 \n"
				 "pretium 1 \n"
				 "Proin 1 \n"
				 "pulvinar 1 7 \n"
				 "purus 1 3 \n"
				 "quam 5 \n"
				 "quis 1 3 5 9 \n"
				 "Quisque 7 \n"
				 "rhoncus 1 5 \n"
				 "risus 3 5 9 \n"
				 "rutrum 3 \n"
				 "sagittis 9 \n"
				 "sapien 1 3 9 \n"
				 "scelerisque 1 9 \n"
				 "sed 1 3 5 7 9 \n"
				 "sem 7 9 \n"
				 "sit 1 3 5 \n"
				 "sodales 3 5 \n"
				 "sollicitudin 3 7 9 \n"
				 "suscipit 1 \n"
				 "Suspendisse 1 \n"
				 "tellus 3 \n"
				 "tempor 1 5 \n"
				 "tempus 1 5 7 \n"
				 "tincidunt 1 5 7 9 \n"
				 "tortor 3 9 \n"
				 "tristique 1 3 5 \n"
				 "turpis 3 5 7 9 \n"
				 "ullamcorper 7 \n"
				 "ultrices 1 7 \n"
				 "ultricies 9 \n"
				 "urna 3 5 7 \n"
				 "Ut 1 3 5 7 9 \n"
				 "varius 3 7 \n"
				 "vel 1 3 5 7 \n"
				 "velit 3 \n"
				 "venenatis 5 9 \n"
				 "vestibulum 3 \n"
				 "vitae 1 3 7 9 \n"
				 "Vivamus 9 \n"
				 "vulputate 3 7 \n", out.str());

}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_woccurrence_with_empty_input));
	s.push_back(CUTE(test_woccurrence_with_one_input_word));
	s.push_back(CUTE(test_woccurrence_with_two_input_words));
	s.push_back(CUTE(test_wordoccurrence_with_one_word_on_multiple_lines));
	s.push_back(CUTE(test_wordoccurrence_with_exercise_example_input));
	s.push_back(CUTE(test_wordoccurrence_with_lorem_ipsum_input));
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
