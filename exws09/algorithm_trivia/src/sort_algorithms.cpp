#include "sort_algorithms.h"
#include "cute.h"
#include "algorithm_replacements.h"

#include <iterator>
#include <algorithm>
#include <vector>
#include <utility>

//Sort algorithms (hint):
// * sort
// * stable_sort
// * partial_sort
// * partial_sort_copy
// * is_sorted
// * nth_element


namespace {

void test_algorithm_1() {
	std::vector<int> in_out1{2, 3, 5, 7, 1, 4, 6, 8, 9};
	std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1));

	ASSERT_EQUAL(expected, in_out1);
}

void test_algorithm_2() {
	std::vector<int> in1{2, 5, 3, 7, 1, 4, 6, 8, 9};
	std::vector<int> out1{0, 0, 0, 0, 0};
	std::vector<int> expected{1, 2, 3, 4, 5};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::begin(out1),
			std::end(out1));

	ASSERT_EQUAL(expected, out1);
}


void test_algorithm_3() {
	std::vector<unsigned> in1{2, 3, 5, 6, 7};

	bool res = std::xxxxx(
			std::begin(in1),
			std::end(in1));

	ASSERT(res);
}


void test_algorithm_4() {
	std::vector<int> in_out1{2, 5, 3, 7, 1, 4, 6, 8, 9};
	std::vector<int> expected{1, 2, 3, 4};

	std::xxxxx(
			std::begin(in_out1),
			std::begin(in_out1) + 4,
			std::end(in_out1));

	ASSERT_EQUAL_RANGES(std::begin(expected), std::end(expected), std::begin(in_out1), std::begin(in_out1) + 4);
}


void test_algorithm_5() {
	std::vector<std::pair<int, int>> in_out1{{2, 1}, {1, 0}, {1, 2}, {1, 4}, {2, 3}};
	std::vector<std::pair<int, int>> expected{{1, 0}, {1, 2}, {1, 4}, {2, 1}, {2, 3}};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1),
			[](std::pair<int, int> l, std::pair<int, int> r) {return l.first < r.first;});

	ASSERT_EQUAL(expected, in_out1);
}


void test_algorithm_6() {
	std::vector<unsigned> in_out1{45, 27, 73, 15, 95, 64, 44, 0, 99};

	std::xxxxx(
			std::begin(in_out1),
			std::begin(in_out1) + 3,
			std::end(in_out1));

	ASSERT_EQUAL(44, *(std::begin(in_out1) + 3));
}

}

cute::suite make_suite_sort_algorithms() {
	cute::suite s { };
	s.push_back(CUTE(test_algorithm_1));
	s.push_back(CUTE(test_algorithm_2));
	s.push_back(CUTE(test_algorithm_3));
	s.push_back(CUTE(test_algorithm_4));
	s.push_back(CUTE(test_algorithm_5));
	s.push_back(CUTE(test_algorithm_6));
	return s;
}
