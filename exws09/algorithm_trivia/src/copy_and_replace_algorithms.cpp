#include "copy_and_replace_algorithms.h"
#include "cute.h"
#include "algorithm_replacements.h"

#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>

//Copy and replace algorithms (hints):
// * copy
// * copy_n
// * copy_if
// * copy_backward
// * swap_ranges
// * transform
// * replace
// * replace_if
// * replace_copy
// * replace_copy_if


namespace {

void test_algorithm_1() {
	std::vector<int> in1{5, 6, 7, 8, 0, 10};
	std::vector<int> out1{};
	std::vector<int> expected{32, 64, 128, 256, 1, 1024};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::back_inserter(out1),
			[](int i){return std::pow(2, i);});

	ASSERT_EQUAL(expected, out1);
}


void test_algorithm_2() {
	std::vector<int> in_out1{1, 2, 3, 2, 1, 2, 3, 2};
	std::vector<int> expected{1, 4, 3, 4, 1, 4, 3, 4};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1),
			2,
			4);

	ASSERT_EQUAL(expected, in_out1);
}

void test_algorithm_3() {
	std::vector<int> in1{1, 2, 3, 2, 1, 2, 3, 2};
	std::vector<int> out1{};
	std::vector<int> expected{1, 4, 3, 4, 1, 4, 3, 4};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::back_inserter(out1),
			2,
			4);

	ASSERT_EQUAL(expected, out1);
}


void test_algorithm_4() {
	std::vector<int> in_out1{1, 2, 3, 4};
	std::vector<int> in_out2{5, 6, 7, 8};
	std::vector<int> expected1{5, 6, 7, 8};
	std::vector<int> expected2{1, 2, 3, 4};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1),
			std::begin(in_out2));

	ASSERT_EQUAL(std::tie(expected1, expected2), std::tie(in_out1, in_out2));
}


void test_algorithm_5() {
	std::vector<int> in_out1{1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int> expected{1, 0, 0, 4, 0, 6, 0, 8};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1),
			is_prime,
			0);

	ASSERT_EQUAL(expected, in_out1);
}

void test_algorithm_6() {
	std::vector<int> in_out1{5, 6, 3, 7, 4, 0, 0, 0};
	std::vector<int> expected{5, 6, 3, 5, 6, 3, 7, 4};

	std::xxxxx(
			std::begin(in_out1),
			std::begin(in_out1) + 5,
			std::end(in_out1));

	ASSERT_EQUAL(expected, in_out1);
}

void test_algorithm_7() {
	std::vector<int> in1{5, 6, 3, 7, 9, 1, 5};
	std::vector<int> out1{};
	std::vector<int> expected{5, 6, 3, 7, 9, 1, 5};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::back_inserter(out1));

	ASSERT_EQUAL(expected, out1);
}

void test_algorithm_8() {
	std::vector<int> in1{5, 6, 3, 7, 10, 10, 5};
	std::vector<int> out1{};
	std::vector<int> expected{5, 3, 7, 5};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::back_inserter(out1),
			[](int const & i) {return i % 2;});

	ASSERT_EQUAL(expected, out1);
}

void test_algorithm_9() {
	std::vector<int> in1{5, 6, 3, 7, 9, 1, 5};
	std::vector<int> out1{};
	std::vector<int> expected{5, 6, 3, 7, 9, 1};

	std::xxxxx(
			std::begin(in1),
			6,
			std::back_inserter(out1));

	ASSERT_EQUAL(expected, out1);
}

void test_algorithm_10() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int> out1{};
	std::vector<int> expected{1, 0, 0, 4, 0, 6, 0, 8};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::back_inserter(out1),
			is_prime,
			0);

	ASSERT_EQUAL(expected, out1);
}

}

cute::suite make_suite_copy_and_replace_algorithms() {
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
	return s;
}
