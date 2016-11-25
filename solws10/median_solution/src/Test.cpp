#include "median.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <algorithm>
#include <vector>

void test_median_with_1_2_3() {
	ASSERT_EQUAL(2, median(1, 2, 3));
}

void test_median_int_right_value() {
	ASSERT_EQUAL(5, median(3, 9, 5));
}

void test_median_double() {
	ASSERT_EQUAL_DELTA(7.0, median(7.0, 7.1, 6.9), 0.0001);
}

void testmedianString() {
	ASSERT_EQUAL("four", median<std::string>("four", "five", "six"));
}

void testmedianCharPtr() {
	ASSERT_EQUAL("four", median("five", "four", "six"));
}

void test_median_all_int_permutations() {
	std::vector<int> v{3, 5, 9};
	do {
		ASSERT_EQUAL(5, median(v[0], v[1], v[2]));
	} while (std::next_permutation(v.begin(), v.end()));
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s;
	s.push_back(CUTE(test_median_double));
	s.push_back(CUTE(test_median_int_right_value));
	s.push_back(CUTE(testmedianString));
	s.push_back(CUTE(testmedianCharPtr));
	s.push_back(CUTE(test_median_all_int_permutations));
	s.push_back(CUTE(test_median_with_1_2_3));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

