#include "min_max_algorithms.h"
#include "cute.h"
#include "algorithm_replacements.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>


//Min-Max algorithms (hint):
// * min
// * max
// * minmax
// * min_element
// * max_element
// * minmax_element


namespace {

void test_algorithm_1() {
	auto expected = 1;

	auto res = std::xxxxx({9, 6, 5, 1, 2, 10, 3, 8});

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_2() {
	std::vector<int> in1{9, 6, 5, 1, 2, 10, 3, 8};
	auto expected = std::begin(in1) + 3;

	auto res = std::xxx(std::begin(in1), std::end(in1));

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_3() {
	std::vector<int> in1{9, 6, 5, 1, 2, 10, 3, 8};
	auto expected = std::make_pair(std::begin(in1) + 3, std::begin(in1) + 5);

	auto res = std::xxxxxx(std::begin(in1), std::end(in1));

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_4() {
	auto expected = 10;

	auto res = std::xxxxx({9, 6, 5, 1, 2, 10, 3, 8});

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_5() {
	auto expected = std::make_pair(1, 10);

	auto res = std::xxxxxx({9, 6, 5, 1, 2, 10, 3, 8});

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_6() {
	std::vector<int> in1{9, 6, 5, 1, 2, 10, 3, 8};
	auto expected = std::begin(in1) + 5;

	auto res = std::xxx(std::begin(in1), std::end(in1));

	ASSERT_EQUAL(expected, res);
}

}

cute::suite make_suite_min_max_algorithms() {
	cute::suite s { };
	s.push_back(CUTE(test_algorithm_1));
	s.push_back(CUTE(test_algorithm_2));
	s.push_back(CUTE(test_algorithm_3));
	s.push_back(CUTE(test_algorithm_4));
	s.push_back(CUTE(test_algorithm_5));
	s.push_back(CUTE(test_algorithm_6));
	return s;
}
