#include "partition_algorithms.h"
#include "cute.h"
#include "algorithm_replacements.h"

#include <vector>
#include <algorithm>
#include <iterator>

//Partition algorithms (hint):
// * is_partitioned
// * partition
// * stable_partition
// * partition_copy
// * partition_point


namespace {

void test_algorithm_1() {
	std::vector<int> in1{2, 3, 5, 7, 1, 4, 6, 8, 9};
	auto expected = std::begin(in1) + 4;

	auto res = std::xxx(
			std::begin(in1),
			std::end(in1),
			is_prime);

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_2() {
	std::vector<int> in_out1{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> expected{2, 3, 5, 7, 1, 4, 6, 8, 9};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1),
			is_prime);

	ASSERT_EQUAL(expected, in_out1);
}

void test_algorithm_3() {
	std::vector<int> in1{2, 3, 5, 7, 1, 4, 6, 8, 9};

	bool res = std::xxxxx(
			std::begin(in1),
			std::end(in1),
			is_prime);

	ASSERT(res);
}


void test_algorithm_4() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> out1{};
	std::vector<int> out2{};
	std::vector<int> expected1{2, 3, 5, 7};
	std::vector<int> expected2{1, 4, 6, 8, 9};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::back_inserter(out1),
			std::back_inserter(out2),
			is_prime);

	ASSERT_EQUAL(std::tie(expected1, expected2), std::tie(out1, out2));
}

void test_algorithm_5() {
	std::vector<int> in_out1{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> expected{7, 2,	3, 5, 4, 6, 1, 8, 9};

	std::xxxxx(
			std::begin(in_out1),
			std::end(in_out1),
			is_prime);

	ASSERT_EQUAL(expected, in_out1);
}

}

cute::suite make_suite_partition_algorithms() {
	cute::suite s { };
	s.push_back(CUTE(test_algorithm_1));
	s.push_back(CUTE(test_algorithm_2));
	s.push_back(CUTE(test_algorithm_3));
	s.push_back(CUTE(test_algorithm_4));
	s.push_back(CUTE(test_algorithm_5));
	return s;
}
