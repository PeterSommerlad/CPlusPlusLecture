#include "set_algorithms.h"
#include "cute.h"
#include "algorithm_replacements.h"

#include <vector>
#include <algorithm>
#include <iterator>

//Set algorithms (hint):
// * includes
// * set_union
// * set_intersection
// * set_difference
// * set_symmetric_difference


namespace {

void test_algorithm_1() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> in2{4, 5, 6, 9, 10, 11, 12};
	std::vector<int> out{};
	std::vector<int> expected{4, 5, 6, 9};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::begin(in2),
			std::end(in2),
			std::back_inserter(out));

	ASSERT_EQUAL(expected, out);
}

void test_algorithm_2() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> in2{4, 5, 6, 9, 10, 11, 12};
	std::vector<int> out{};
	std::vector<int> expected{1, 2, 3, 7, 8};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::begin(in2),
			std::end(in2),
			std::back_inserter(out));

	ASSERT_EQUAL(expected, out);
}

void test_algorithm_3() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> in2{4, 5, 6, 9, 10, 11, 12};
	std::vector<int> out{};
	std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::begin(in2),
			std::end(in2),
			std::back_inserter(out));

	ASSERT_EQUAL(expected, out);
}


void test_algorithm_4() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> in2{4, 5, 6, 9, 10, 11, 12};
	std::vector<int> out{};
	std::vector<int> expected{1, 2, 3, 7, 8, 10, 11, 12};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::begin(in2),
			std::end(in2),
			std::back_inserter(out));

	ASSERT_EQUAL(expected, out);
}


void test_algorithm_5() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> in2{2, 3, 4, 7, 8, 9};

	auto res = std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::begin(in2),
			std::end(in2));

	ASSERT(res);
}

}

cute::suite make_suite_set_algorithms() {
	cute::suite s { };
	s.push_back(CUTE(test_algorithm_1));
	s.push_back(CUTE(test_algorithm_2));
	s.push_back(CUTE(test_algorithm_3));
	s.push_back(CUTE(test_algorithm_4));
	s.push_back(CUTE(test_algorithm_5));
	return s;
}
