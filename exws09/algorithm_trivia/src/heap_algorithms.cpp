#include "heap_algorithms.h"
#include "cute.h"
#include "algorithm_replacements.h"

#include <vector>
#include <algorithm>
#include <iterator>

//Heap algorithms (hint):
// * push_heap
// * pop_heap
// * make_heap
// * sort_heap
// * is_heap_until
// * is_heap


namespace {

void test_algorithm_1() {
	std::vector<int> in_out1{10, 6, 9, 1, 2, 3, 5};
	std::vector<int> expected{1, 2, 3, 5, 6, 9, 10};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1));

	ASSERT_EQUAL(expected, in_out1);
}


void test_algorithm_2() {
	std::vector<int> in_out1{9, 6, 5, 1, 2, 3, 10};
	std::vector<int> expected{10, 6, 9, 1, 2, 3, 5};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1));

	ASSERT_EQUAL(expected, in_out1);
}

void test_algorithm_3() {
	std::vector<int> in1{10, 6, 9, 1, 2, 3, 5};

	auto res = std::xxxxx(
			std::begin(in1),
			std::end(in1));

	ASSERT(res);
}

void test_algorithm_4() {
	std::vector<int> in_out1{10, 6, 9, 1, 2, 3, 5};
	std::vector<int> expected{9, 6, 5, 1, 2, 3, 10};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1));

	ASSERT_EQUAL(expected, in_out1);
}

void test_algorithm_5() {
	std::vector<int> in1{9, 6, 5, 1, 2, 3, 10};
	auto expected = std::begin(in1) + 6;

	auto res = std::xxx(
			std::begin(in1),
			std::end(in1));

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_6() {
	std::vector<int> in_out1{3, 1, 9, 2, 5, 6, 10};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1));

	ASSERT(std::is_heap(std::begin(in_out1), std::end(in_out1)));
}

}

cute::suite make_suite_heap_algorithms() {
	cute::suite s { };
	s.push_back(CUTE(test_algorithm_1));
	s.push_back(CUTE(test_algorithm_2));
	s.push_back(CUTE(test_algorithm_3));
	s.push_back(CUTE(test_algorithm_4));
	s.push_back(CUTE(test_algorithm_5));
	s.push_back(CUTE(test_algorithm_6));
	return s;
}
