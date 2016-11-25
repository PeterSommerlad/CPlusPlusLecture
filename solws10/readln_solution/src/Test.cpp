#include "readln.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <sstream>
#include <string>

void emptyreadlntest() {
	std::istringstream in { "" };
	int var { };
	readln(in, var);
	ASSERT(in.fail());
}
void failedreadlntest() {
	std::istringstream in { "a\n" };
	int var { };
	readln(in, var);
	ASSERT(in.fail());
}
void successfulreadlntestwithoutlineend() {
	std::istringstream in { "42" };
	int var { };
	readln(in, var);
	ASSERT_EQUAL(42, var);
	ASSERT(!in.fail());
}

void readlnwithstringconsumestoeol() {
	std::istringstream in { "1 some rest 123\n2the rest\n" };
	std::string rest { };
	int first { };
	readln(in, first, rest);
	ASSERT_EQUAL(1, first);
	ASSERT_EQUAL(" some rest 123", rest);
	readln(in, first, rest);
	ASSERT_EQUAL(2, first);
	ASSERT_EQUAL("the rest", rest);

}

void testNonStringAtEnd() {
	std::istringstream in { "1 2 3\n" };
	int a { }, b { }, c { }, d { };
	readln(in, a, b, c, d);
	ASSERT_EQUAL(1, a);
	ASSERT_EQUAL(0, d);
}

void longreadlntest() {
	std::istringstream in { "one 1 two \02 three 3.0\nthe rest\n" };
	std::string one { };
	std::string two { };
	std::string three { };
	int ione { };
	char ctwo { };
	double dthree { };

	readln(in, one, ione, two, ctwo, three, dthree);
	std::string rest;
	readln(in, rest);
	ASSERT_EQUAL("one", one);
	ASSERT_EQUAL("two", two);
	ASSERT_EQUAL("three", three);
	ASSERT_EQUAL(1, ione);
	ASSERT_EQUAL('\02', ctwo);
	ASSERT_EQUAL(3.0, dthree);
	ASSERT_EQUAL("the rest", rest);
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s;
	s.push_back(CUTE(longreadlntest));
	s.push_back(CUTE(emptyreadlntest));
	s.push_back(CUTE(failedreadlntest));
	s.push_back(CUTE(successfulreadlntestwithoutlineend));
	s.push_back(CUTE(readlnwithstringconsumestoeol));
	s.push_back(CUTE(testNonStringAtEnd));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

