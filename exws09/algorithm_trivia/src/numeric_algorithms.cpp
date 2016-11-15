#include "numeric_algorithms.h"
#include "cute.h"
#include "algorithm_replacements.h"

#include <vector>
#include <numeric>
#include <iterator>
#include <string>

//Numeric algorithms (hint):
// * accumulate
// * inner_product
// * partial_sum
// * adjacent_difference
// * iota


namespace {

void test_algorithm_1() {
	std::vector<int> out1(8);
	std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7};

	std::xxxxx(
			std::begin(out1),
			std::end(out1),
			0);

	ASSERT_EQUAL(expected, out1);
}

void test_algorithm_2() {
	std::vector<int> in1{1, 2, 4, 3, 9, 5, 7};
	std::vector<int> out1(in1.size());
	std::vector<int> expected{1, 1, 2, -1, 6, -4, 2};

	std::xxxxx(
			std::begin(in1),
			std::end(in1),
			std::begin(out1));

	ASSERT_EQUAL(expected, out1);
}

void test_algorithm_3() {
	std::vector<int> in1{1, 2, 3, 4, 5, 6};
	int expected = 121;

	int res = std::xxxxx(
			std::begin(in1),
			std::end(in1),
			100);

	ASSERT_EQUAL(expected, res);
}

void test_algorithm_4() {
	std::vector<int> in1{1, 20, 300, 4000, 50000};
	std::vector<int> out1(in1.size());
	std::vector<int> expected{1, 21,321,4321, 54321};

	std::xxxxxx(std::begin(in1), std::end(in1), std::begin(out1));

	ASSERT_EQUAL(expected, out1);
}

void test_algorithm_5() {
	std::vector<int> in1{1, 2, 3, 2, 1};
	std::vector<char> in2{'a', 'b', 'c', 'd', 'e'};
	std::string expected{"begin, 1a, 2b, 3c, 2d, 1e"};

	std::string res = std::xxxx(
			std::begin(in1),
			std::end(in1),
			std::begin(in2),
			std::string{"begin"},
			[](std::string l, std::string r) {return l + ", " + r;},
			[](int i, char c) {return std::to_string(i) + c;});

	ASSERT_EQUAL(expected, res);
}

}

cute::suite make_suite_numeric_algorithms() {
	cute::suite s { };
	s.push_back(CUTE(test_algorithm_1));
	s.push_back(CUTE(test_algorithm_2));
	s.push_back(CUTE(test_algorithm_3));
	s.push_back(CUTE(test_algorithm_4));
	s.push_back(CUTE(test_algorithm_5));
	return s;
}
