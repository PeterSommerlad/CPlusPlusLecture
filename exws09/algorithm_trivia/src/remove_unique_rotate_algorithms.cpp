#include "remove_unique_rotate_algorithms.h"
#include "cute.h"
#include "algorithm_replacements.h"

#include <vector>
#include <algorithm>
#include <iterator>

//Remove, unique and rotate algorithms (hint):
// * remove
// * remove_if
// * remove_copy
// * remove_copy_if
// * unique
// * unique_copy
// * reverse
// * reverse_copy
// * rotate
// * rotate_copy
// * next_permutation
// * prev_permutation


namespace {

void test_algorithm_1() {
	std::vector<int> in1{5, 6, 7, 8, 0, 10};
	std::vector<int> out1{};
	std::vector<int> expected{10, 0, 8, 7, 6, 5};

	std::xxxxxx(
			std::begin(in1),
			std::end(in1),
			std::back_inserter(out1));

	ASSERT_EQUAL(expected, out1);
}

void test_algorithm_2() {
	std::vector<int> in_out1{4, 1, 2, 3};
	std::vector<int> expected{3, 4, 2, 1};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1));

	ASSERT_EQUAL(expected, in_out1);
}

void test_algorithm_3() {
	std::vector<int> in_out1{1, 1, 3, 3, 4, 2, 2, 2};
	std::vector<int> expected{1, 3, 4, 2};

	auto new_end = std::xxx(
			std::begin(in_out1),
			std::end(in_out1));

	ASSERT_EQUAL_RANGES(std::begin(expected), std::end(expected), std::begin(in_out1), new_end);
}

void test_algorithm_4() {
	std::vector<int> in_out1{1, 2, 3, 2, 1, 2, 3, 2};
	std::vector<int> expected{1, 3, 1, 3};

	auto new_end = std::xxx(
			std::begin(in_out1),
			std::end(in_out1),
			2);

	ASSERT_EQUAL_RANGES(std::begin(expected), std::end(expected), std::begin(in_out1), new_end);
}

void test_algorithm_5() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> out1{};
	std::vector<int> expected{5, 6, 7, 8, 9, 1, 2, 3, 4};

	std::xxxxx(
			std::begin(in1),
			std::begin(in1) + 4,
			std::end(in1),
			std::back_inserter(out1));

	ASSERT_EQUAL(expected, out1);
}

void test_algorithm_6() {
	std::vector<int> in_out1{5, 6, 7, 8, 0, 10};
	std::vector<int> expected{10, 0, 8, 7, 6, 5};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1));

	ASSERT_EQUAL(expected, in_out1);
}

void test_algorithm_7() {
	std::vector<int> in_out1{4, 1, 2, 3};
	std::vector<int> expected{4, 1, 3, 2};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1));

	ASSERT_EQUAL(expected, in_out1);
}

void test_algorithm_8() {
	std::vector<int> in_out1{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> expected{5, 6, 7, 8, 9, 1, 2, 3, 4};

	std::xxxxx(
			std::begin(in_out1),
			std::begin(in_out1) + 4,
			std::end(in_out1));

	ASSERT_EQUAL(expected, in_out1);
}


void test_algorithm_9() {
	std::vector<int> in_out1{1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int> expected{1, 4, 6, 8};

	auto new_end = std::xxx(
			std::begin(in_out1),
			std::end(in_out1),
			is_prime);

	ASSERT_EQUAL_RANGES(std::begin(expected), std::end(expected), std::begin(in_out1), new_end);
}

void test_algorithm_10() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int> out1{};
	std::vector<int> expected{1, 4, 6, 8};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::back_inserter(out1),
			is_prime);

	ASSERT_EQUAL(expected, out1);
}


void test_algorithm_11() {
	std::vector<int> in1{1, 2, 3, 2, 1, 2, 3, 2};
	std::vector<int> out1{};
	std::vector<int> expected{1, 3, 1, 3};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::back_inserter(out1),
			2);

	ASSERT_EQUAL(expected, out1);
}

void test_algorithm_12() {
	std::vector<int> in1{1, 1, 3, 3, 4, 2, 2, 2};
	std::vector<int> out1{};
	std::vector<int> expected{1, 3, 4, 2};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::back_inserter(out1));

	ASSERT_EQUAL(expected, out1);
}

}

cute::suite make_suite_remove_unique_rotate_algorithms() {
	cute::suite s { };
	s.push_back(CUTE(test_algorithm_1));
	s.push_back(CUTE(test_algorithm_2));
	s.push_back(CUTE(test_algorithm_3));
	s.push_back(CUTE(test_algorithm_4));
	s.push_back(CUTE(test_algorithm_5));
	s.push_back(CUTE(test_algorithm_6));
	s.push_back(CUTE(test_algorithm_7));
	s.push_back(CUTE(test_algorithm_8));
	s.push_back(CUTE(test_algorithm_9));
	s.push_back(CUTE(test_algorithm_10));
	s.push_back(CUTE(test_algorithm_11));
	s.push_back(CUTE(test_algorithm_12));
	return s;
}
