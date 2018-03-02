#include "readln.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <sstream>
#include <string>

void test_readln_empty_input() {
	std::istringstream in { "" };
	int var { };
	readln(in, var);
	ASSERT(in.fail());
}
void test_readln_failed_on_wrong_format() {
	std::istringstream in { "a\n" };
	int var { };
	readln(in, var);
	ASSERT(in.fail());
}
void test_readln_successful__without_line_end() {
	std::istringstream in { "42" };
	int var { };
	readln(in, var);
	ASSERT_EQUAL(42, var);
	ASSERT(!in.fail());
}


void test_readln_non_string_at_end() {
	std::istringstream in { "1 2 3\n" };
	int a { }, b { }, c { }, d { };
	readln(in, a, b, c, d);
	ASSERT_EQUAL(1, a);
	ASSERT_EQUAL(0, d);
}

void test_readln_multiple_mixed_inputs() {
	std::istringstream in { "one 1 two \02 three 3.0\nthe rest\n" };
	std::string one { };
	std::string two { };
	std::string three { };
	int ione { };
	char ctwo { };
	double dthree { };

	readln(in, one, ione, two, ctwo, three, dthree);
	ASSERT_EQUAL("one", one);
	ASSERT_EQUAL("two", two);
	ASSERT_EQUAL("three", three);
	ASSERT_EQUAL(1, ione);
	ASSERT_EQUAL('\02', ctwo);
	ASSERT_EQUAL(3.0, dthree);
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s;
	s.push_back(CUTE(test_readln_multiple_mixed_inputs));
	s.push_back(CUTE(test_readln_empty_input));
	s.push_back(CUTE(test_readln_failed_on_wrong_format));
	s.push_back(CUTE(test_readln_successful__without_line_end));
	s.push_back(CUTE(test_readln_non_string_at_end));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

