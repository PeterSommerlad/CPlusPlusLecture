#include "rotate3arguments.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <tuple>

void rotate3ints() {
	int a { 1 }, b { 2 }, c { 3 };
	auto expected = std::make_tuple(2, 3, 1);

	rotate3arguments(a, b, c);

	ASSERT_EQUAL(expected, std::tie(a, b, c));
}

void rotate3strings() {
	auto a = "one", b = "two", c = "three";
	auto expected = std::make_tuple("two", "three", "one");

	rotate3arguments(a, b, c);

	ASSERT_EQUAL(expected, std::tie(a, b, c));
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s;
	s.push_back(CUTE(rotate3ints));
	s.push_back(CUTE(rotate3strings));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

