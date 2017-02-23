#include "Fraction.h"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <sstream>

void testDefaultValueIsZero() {
	ASSERT_EQUAL(Fraction { 0 }, Fraction { });
}

void testSameFractionIsEqual() {
	ASSERT_EQUAL(Fraction { 1 }, Fraction { 1 });
}

void testDifferentFractionIsNotEqual() {
	ASSERT_NOT_EQUAL_TO(Fraction { 1 }, Fraction { 2 });
}

void testSameFractionWithDifferentDenominatorIsEqual() {
	ASSERT_EQUAL((Fraction { 1, 2 }), (Fraction { 2, 4 }));
}

void testUnaryMinus() {
	ASSERT_EQUAL((Fraction { -15, 23 }), (-Fraction { 15, 23 }));
}

void testUnaryPlus() {
	ASSERT_EQUAL((Fraction { 15, 23 }), (+Fraction { 15, 23 }));
}

void testPrintFraction() {
	std::ostringstream out { };
	Fraction const f { 1, 2 };
	out << f;
	ASSERT_EQUAL("1/2", out.str());
}

void testReadFraction() {
	Fraction expected { 6, 5 };
	std::istringstream input { "30/25" };
	Fraction value { };
	input >> value;
	ASSERT_EQUAL(expected, value);
}

void testAddAssignFractions() {
	Fraction const expected { 3, 4 };
	Fraction result { 1, 2 };
	Fraction const quarter { 1, 4 };
	result += quarter;
	ASSERT_EQUAL(expected, result);
}

void testAddFractions() {
	Fraction const expected { 3, 4 };
	Fraction const half { 1, 2 };
	Fraction const quarter { 1, 4 };
	ASSERT_EQUAL(expected, half + quarter);
}

void testAddAssignReduces() {
	Fraction const expected { 3, 2 };
	Fraction result { 3, 4 };
	result += result;
	ASSERT_EQUAL(expected, result);
}

void testSubstractAssignFractions() {
	Fraction const expected { 1, 5 };
	Fraction result { 3, 5 };
	Fraction const half { 2, 5 };
	result -= half;
	ASSERT_EQUAL(expected, result);
}

void testSubstractFractions() {
	Fraction const expected { 7, 10 };
	Fraction const one { 1 };
	Fraction const three_tenth { 3, 10 };
	ASSERT_EQUAL(expected, one - three_tenth);
}

void testSubtractAssignReduces() {
	Fraction const expected { 1, 5 };
	Fraction result { 7, 10 };
	Fraction const half { 1, 2 };
	result -= half;
	ASSERT_EQUAL(expected, result);
}

void testMultAssignFractions() {
	Fraction const expected { 7, 15 };
	Fraction result { 7, 5 };
	Fraction const third { 1, 3 };
	result *= third;
	ASSERT_EQUAL(expected, result);
}

void testMultFractions() {
	Fraction const expected { 2, 9 };
	Fraction const third { 1, 3 };
	Fraction const two_thirds { 2, 3 };
	ASSERT_EQUAL(expected, third * two_thirds);
}

void testMultAssignReduces() {
	Fraction const expected { 1, 2 };
	Fraction result { 3, 4 };
	Fraction const two_thirds { 2, 3 };
	result *= two_thirds;
	ASSERT_EQUAL(expected, result);
}

void testDivAssignFractions() {
	Fraction const expected { 21, 10 };
	Fraction result { 7, 5 };
	Fraction const third { 2, 3 };
	result /= third;
	ASSERT_EQUAL(expected, result);
}

void testDivFractions() {
	Fraction const expected { 7, 15 };
	Fraction const third { 1, 3 };
	Fraction const five_seventh { 5, 7 };
	ASSERT_EQUAL(expected, third / five_seventh);
}

void testDivAssignReduces() {
	Fraction const expected { 1, 2 };
	Fraction result { 1, 3 };
	Fraction const two_thirds { 2, 3 };
	result /= two_thirds;
	ASSERT_EQUAL(expected, result);
}

void testLessThanFraction() {
	Fraction const smaller { 1, 2 };
	Fraction const bigger { 2, 3 };
	ASSERT_LESS(smaller, bigger);
}

void testLessOrEqualFractionWithSamller() {
	Fraction const smaller { 1, 2 };
	Fraction const bigger { 2, 3 };
	ASSERT_LESS_EQUAL(smaller, bigger);
}

void testLessOrEqualFractionWithEqual() {
	Fraction const f { 7, 15 };
	ASSERT_LESS_EQUAL(f, f);
}

void testGreaterThan() {
	Fraction const smaller { 1, 2 };
	Fraction const bigger { 2, 3 };
	ASSERT_GREATER(bigger, smaller);
}

void testGreaterOrEqualFractionWithGreater() {
	Fraction const smaller { 1, 2 };
	Fraction const bigger { 2, 3 };
	ASSERT_GREATER_EQUAL(bigger, smaller);
}

void testGreaterOrEqualFractionWithEqual() {
	Fraction const f { 7, 15 };
	ASSERT_LESS_EQUAL(f, f);
}

void testPrefixIncrement() {
	Fraction const expected{8, 5};
	Fraction result{3, 5};
	++result;
	ASSERT_EQUAL(expected, result);
}

void testPostfixIncrement() {
	Fraction const expected{8, 5};
	Fraction result{3, 5};
	result++;
	ASSERT_EQUAL(expected, result);
}


void testPrefixDecrement() {
	Fraction const expected{8, 5};
	Fraction result{13, 5};
	--result;
	ASSERT_EQUAL(expected, result);
}

void testPostfixDecrement() {
	Fraction const expected{8, 5};
	Fraction result{13, 5};
	result--;
	ASSERT_EQUAL(expected, result);
}

void testNegativeNumeratorDenomiatorEquality() {
	Fraction const expected{-13, 27};
	Fraction const actual{13, -27};
	ASSERT_EQUAL(expected, actual);
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testSameFractionIsEqual));
	s.push_back(CUTE(testDifferentFractionIsNotEqual));
	s.push_back(CUTE(testSameFractionWithDifferentDenominatorIsEqual));
	s.push_back(CUTE(testAddAssignFractions));
	s.push_back(CUTE(testAddFractions));
	s.push_back(CUTE(testAddAssignReduces));
	s.push_back(CUTE(testPrintFraction));
	s.push_back(CUTE(testSubstractAssignFractions));
	s.push_back(CUTE(testSubstractFractions));
	s.push_back(CUTE(testSubtractAssignReduces));
	s.push_back(CUTE(testUnaryMinus));
	s.push_back(CUTE(testUnaryPlus));
	s.push_back(CUTE(testMultAssignFractions));
	s.push_back(CUTE(testMultFractions));
	s.push_back(CUTE(testMultAssignReduces));
	s.push_back(CUTE(testDivAssignFractions));
	s.push_back(CUTE(testDivFractions));
	s.push_back(CUTE(testDivAssignReduces));
	s.push_back(CUTE(testDefaultValueIsZero));
	s.push_back(CUTE(testReadFraction));
	s.push_back(CUTE(testLessThanFraction));
	s.push_back(CUTE(testLessOrEqualFractionWithSamller));
	s.push_back(CUTE(testLessOrEqualFractionWithEqual));
	s.push_back(CUTE(testGreaterThan));
	s.push_back(CUTE(testGreaterOrEqualFractionWithGreater));
	s.push_back(CUTE(testGreaterOrEqualFractionWithEqual));
	s.push_back(CUTE(testPrefixIncrement));
	s.push_back(CUTE(testPostfixIncrement));
	s.push_back(CUTE(testPrefixDecrement));
	s.push_back(CUTE(testPostfixDecrement));
	s.push_back(CUTE(testNegativeNumeratorDenomiatorEquality));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
	return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
