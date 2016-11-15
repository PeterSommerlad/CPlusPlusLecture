#include "find_algorithms.h"
#include "cute.h"
#include "algorithm_replacements.h"

#include <vector>
#include <algorithm>
#include <iterator>


//Find and related algorithms (hint):
// * find
// * find_if
// * find_if_not
// * find_end
// * find_first_of
// * adjacent_find
// * count
// * count_if
// * search
// * search_n


namespace {

void test_algorithm_1() {
	std::vector<int> in1{1, 2, 1, 2, 1, 2, 3, 1, 2, 3};
	std::vector<int> in2{1, 2, 3};
	auto expected = std::begin(in1) + 4;

	auto res = std::xxx(
			std::begin(in1),
			std::end(in1),
			std::begin(in2),
			std::end(in2));

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_2() {
	std::vector<int> in1{1, 2, 3, 2, 1, 2, 3, 4, 3, 2};
	int expected = 4;

	int res = std::xxxxx(
			std::begin(in1),
			std::end(in1),
			2);

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_3() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7};
	auto expected = std::begin(in1) + 4;

	auto res = std::xxx(
			std::begin(in1),
			std::end(in1),
			5);

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_4() {
	std::vector<int> in1{5, 6, 4, 7, 6, 2, 1};
	std::vector<int> in2{1, 2, 3};
	auto expected = std::begin(in1) + 5;

	auto res = std::xxx(
			std::begin(in1),
			std::end(in1),
			std::begin(in2),
			std::end(in2));

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_5() {
	std::vector<int> in1{1, 1, 2, 2, 2, 1, 1, 1, 3, 3};
	auto expected = std::begin(in1) + 5;

	auto res = std::xxx(
			std::begin(in1),
			std::end(in1),
			3,
			1);

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_6() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7};
	auto expected = std::begin(in1) + 1;

	auto res = std::xxx(
			std::begin(in1),
			std::end(in1),
			is_prime);

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_7() {
	std::vector<int> in1{5, 6, 4, 7, 7, 2, 2};
	auto expected = std::begin(in1) + 3;

	auto res = std::xxx(
			std::begin(in1),
			std::end(in1));

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_8() {
	std::vector<int> in1{2, 3, 5, 7, 11, 13, 17};
	auto expected = std::end(in1);

	auto res = std::xxx(
			std::begin(in1),
			std::end(in1),
			is_prime);

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_9() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int expected = 4;

	int res = std::xxxxx(
			std::begin(in1),
			std::end(in1),
			is_prime);

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_10() {
	std::vector<int> in1{1, 2, 3, 1, 2, 3, 1};
	std::vector<int> in2{1, 2, 3};
	auto expected = std::begin(in1) + 3;

	auto res = std::xxx(
			std::begin(in1),
			std::end(in1),
			std::begin(in2),
			std::end(in2));

	ASSERT_EQUAL(expected, res);
}

}

cute::suite make_suite_find_algorithms() {
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
