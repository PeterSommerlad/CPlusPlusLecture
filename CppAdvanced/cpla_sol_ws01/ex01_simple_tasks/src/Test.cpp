#include "increment.h"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <limits>
#include <stdexcept>
#include <vector>
#include <iterator>

void testIncrementReturnsOneForZero() {
	ASSERT_EQUAL(1, increment_by_value(0));
}

void testIncrementReturns42For41() {
	ASSERT_EQUAL(42, increment_by_value(41));
}

void testIncrementSideEffectOneForZero() {
	int i{0};
	increment(i);
	ASSERT_EQUAL(1, i);
}

void testIncrementSideEffect42For41() {
	int i{41};
	increment(i);
	ASSERT_EQUAL(42, i);
}

void testMaxIntCannotBeIncremented() {
	int i{std::numeric_limits<int>::max()};
	ASSERT_THROWS(increment(i), std::overflow_error);
}

void testIncrementDoesNotChangeParameterOnError() {
	int i{std::numeric_limits<int>::max()};
	try {
		increment(i);
	} catch (std::overflow_error const &) {
		ASSERT_EQUAL(std::numeric_limits<int>::max(), i);
	}
}

void testIncrementDoubleZeroToOne() {
	double i{0.0};
	increment(i);
	ASSERT_EQUAL(1.0, i);
}

void testIncrementUnsignedLongLongOverflow() {
	unsigned long long max = std::numeric_limits<unsigned long long>::max();
	unsigned long long const expected = std::numeric_limits<unsigned long long>::min();
	increment(max);
	ASSERT_EQUAL(expected, max);
}

void testIncrementUnsignedOverflow() {
	unsigned max = std::numeric_limits<unsigned>::max();
	unsigned const expected = std::numeric_limits<unsigned>::min();
	increment(max);
	ASSERT_EQUAL(expected, max);
}

void testIncrementUnsignedCharOverflow() {
	unsigned char max = std::numeric_limits<unsigned char>::max();
	unsigned char const expected = std::numeric_limits<unsigned char>::min();
	increment(max);
	ASSERT_EQUAL(expected, max);
}

void testIncrementSignedCharOverflowThrows() {
	char max = std::numeric_limits< char>::max();
	ASSERT_THROWS(increment(max), std::overflow_error);
}

void testIncrementIterator() {
	std::vector<int> v{1};
	auto it = std::begin(v);
	increment(it, std::end(v));
	ASSERT_EQUAL(std::end(v), it);
}

void testIncrementEndIteratorThrows() {
	std::vector<int> v{1};
	auto it = std::end(v);
	ASSERT_THROWS(increment(it, std::end(v)), std::overflow_error);
}

void testIncrementWithCustomLimitThrows() {
	double d{9.5};
	ASSERT_THROWS(increment(d, 9.0), std::overflow_error);
}

//void testIncrementWithCustomLimitIncrementsSublimit() {
//	double d{9.5};
//	increment(d, 10.0);
//	ASSERT_EQUAL(10.5, d);
//}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testIncrementReturnsOneForZero));
	s.push_back(CUTE(testIncrementReturns42For41));
	s.push_back(CUTE(testIncrementSideEffectOneForZero));
	s.push_back(CUTE(testIncrementSideEffect42For41));
	s.push_back(CUTE(testMaxIntCannotBeIncremented));
	s.push_back(CUTE(testIncrementDoesNotChangeParameterOnError));
	s.push_back(CUTE(testIncrementDoubleZeroToOne));
	s.push_back(CUTE(testIncrementIterator));
	s.push_back(CUTE(testIncrementEndIteratorThrows));
	s.push_back(CUTE(testIncrementWithCustomLimitThrows));
//	s.push_back(CUTE(testIncrementWithCustomLimitIncrementsSublimit));
	s.push_back(CUTE(testIncrementUnsignedOverflow));
	s.push_back(CUTE(testIncrementUnsignedLongLongOverflow));
	s.push_back(CUTE(testIncrementUnsignedCharOverflow));
	s.push_back(CUTE(testIncrementSignedCharOverflowThrows));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
