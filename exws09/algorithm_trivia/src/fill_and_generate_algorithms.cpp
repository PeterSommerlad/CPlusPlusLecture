#include "fill_and_generate_algorithms.h"
#include "cute.h"
#include "algorithm_replacements.h"

#include <vector>
#include <algorithm>
#include <iterator>

//Fill and generate algorithms (hints):
// * fill
// * fill_n
// * generate
// * generate_n

namespace {

void test_algorithm_1() {
	std::vector<int> in_out1{1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int> expected{42, 42, 42, 42, 5, 6, 7, 8};

	std::xxxxx(
			std::begin(in_out1),
			4,
			42);

	ASSERT_EQUAL(expected, in_out1);
}


void test_algorithm_2() {
	std::vector<int> out1{};
	std::vector<int> expected{100, 101, 102, 103, 104};
	int start = 100;

	std::xxxxx(
			std::back_inserter(out1),
			5,
			[start]() mutable {return start++;});

	ASSERT_EQUAL(expected, out1);
}

void test_algorithm_3() {
	std::vector<int> out1(5);
	std::vector<int> expected{100, 101, 102, 103, 104};
	int start = 100;

	std::xxxxx(
			std::begin(out1),
			std::end(out1),
			[start]() mutable {return start++;});

	ASSERT_EQUAL(expected, out1);
}

void test_algorithm_4() {
	std::vector<int> in_out1{1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int> expected{42, 42, 42, 42, 42, 42, 42, 42};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1),
			42);

	ASSERT_EQUAL(expected, in_out1);
}

}

cute::suite make_suite_fill_and_generate_algorithms() {
	cute::suite s { };
	s.push_back(CUTE(test_algorithm_1));
	s.push_back(CUTE(test_algorithm_2));
	s.push_back(CUTE(test_algorithm_3));
	s.push_back(CUTE(test_algorithm_4));
	return s;
}
