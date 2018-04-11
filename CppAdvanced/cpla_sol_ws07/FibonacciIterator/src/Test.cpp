#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "FibonacciIterator.h"



void test_default_constructed_iterator_returns_zero() {
	FibonacciIterator const fibItr{};

	ASSERT_EQUAL(0, *fibItr);
}

void test_fibonacci_iterator_for_first_element_is_one() {
	FibonacciIterator const fibItr{1};

	ASSERT_EQUAL(1, *fibItr);
}

void test_fibonacci_iterator_for_second_element_is_one() {
	FibonacciIterator const fibItr{2};

	ASSERT_EQUAL(1, *fibItr);
}

void test_fibonacci_iterator_for_third_element_is_two() {
	FibonacciIterator const fibItr{3};

	ASSERT_EQUAL(2, *fibItr);
}

void test_fibonacci_iterator_for_fourth_element_is_three() {
	FibonacciIterator const fibItr{4};

	ASSERT_EQUAL(3, *fibItr);
}

void test_fibonacci_iterator_for_fifth_element_is_five() {
	FibonacciIterator const fibItr{5};

	ASSERT_EQUAL(5, *fibItr);
}

void test_fibonacci_iterator_for_sixth_element_is_eight() {
	FibonacciIterator const fibItr{6};

	ASSERT_EQUAL(8, *fibItr);
}

void test_fibonacci_iterator_for_seventh_element_is_thirteen() {
	FibonacciIterator const fibItr{7};

	ASSERT_EQUAL(13, *fibItr);
}

void test_fibonacci_iterator_for_eighth_element_is_twentyone() {
	FibonacciIterator const fibItr{8};

	ASSERT_EQUAL(21, *fibItr);
}

void test_fibonacci_iterator_for_ninth_element_is_thirtyfour() {
	FibonacciIterator const fibItr{9};

	ASSERT_EQUAL(34, *fibItr);
}

void test_fibonacci_iterator_for_tenth_element_is_fiftyfive() {
	FibonacciIterator const fibItr{10};

	ASSERT_EQUAL(55, *fibItr);
}

void test_fibonacci_iterator_equal_to_itself() {
	FibonacciIterator const fibItr{};

	ASSERT_EQUAL(fibItr, fibItr);
}

void test_fibonacci_iterator_equal_to_other_fibonacci_iterator_with_same_state() {
	FibonacciIterator const fibItr{10}, otherFibItr{10};

	ASSERT_EQUAL(fibItr, otherFibItr);
}

void test_fibonacci_iterator_not_equal_to_other_fibonacci_iterator_with_another_state() {
	FibonacciIterator const fibItr{5}, otherFibItr{10};

	ASSERT_NOT_EQUAL_TO(fibItr, otherFibItr);
}

void test_prefix_incrementing_default_fibonacci_iterator_increments_this_fibonacci_iterator() {
	FibonacciIterator const expectedItr{1};
	FibonacciIterator otherFibItr{};

	++otherFibItr;

	ASSERT_EQUAL(expectedItr, otherFibItr);
}

void test_prefix_incrementing_default_fibonacci_iterator_returns_changed_fibonacci_iterator() {
	FibonacciIterator fibItr{};

	FibonacciIterator& changed { ++fibItr };

	ASSERT_EQUAL(&changed, &fibItr);
}

void test_postfix_incrementing_default_fibonacci_iterator_increments_this_fibonacci_iterator() {
	FibonacciIterator const expectedItr{1};
	FibonacciIterator otherFibItr{};

	++otherFibItr;

	ASSERT_EQUAL(expectedItr, otherFibItr);
}

void test_postfix_incrementing_default_fibonacci_iterator_returns_previous_value_fibonacci_iterator() {
	FibonacciIterator const expectedItr{};
	FibonacciIterator otherFibItr{};

	FibonacciIterator const unincremented { otherFibItr++ };

	ASSERT_EQUAL(expectedItr, unincremented);
}

void test_postfix_incrementing_default_fibonacci_iterator_returns_new_fibonacci_iterator() {
	FibonacciIterator fibItr{};

	FibonacciIterator const & changed { fibItr++ };

	ASSERT_NOT_EQUAL_TO(&changed, &fibItr);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(test_default_constructed_iterator_returns_zero));
	s.push_back(CUTE(test_fibonacci_iterator_for_first_element_is_one));
	s.push_back(CUTE(test_fibonacci_iterator_for_second_element_is_one));
	s.push_back(CUTE(test_fibonacci_iterator_for_third_element_is_two));
	s.push_back(CUTE(test_fibonacci_iterator_for_fourth_element_is_three));
	s.push_back(CUTE(test_fibonacci_iterator_for_fifth_element_is_five));
	s.push_back(CUTE(test_fibonacci_iterator_for_sixth_element_is_eight));
	s.push_back(CUTE(test_fibonacci_iterator_for_seventh_element_is_thirteen));
	s.push_back(CUTE(test_fibonacci_iterator_for_eighth_element_is_twentyone));
	s.push_back(CUTE(test_fibonacci_iterator_for_ninth_element_is_thirtyfour));
	s.push_back(CUTE(test_fibonacci_iterator_for_tenth_element_is_fiftyfive));
	s.push_back(CUTE(test_fibonacci_iterator_equal_to_itself));
	s.push_back(CUTE(test_fibonacci_iterator_equal_to_other_fibonacci_iterator_with_same_state));
	s.push_back(CUTE(test_fibonacci_iterator_not_equal_to_other_fibonacci_iterator_with_another_state));
	s.push_back(CUTE(test_prefix_incrementing_default_fibonacci_iterator_increments_this_fibonacci_iterator));
	s.push_back(CUTE(test_prefix_incrementing_default_fibonacci_iterator_returns_changed_fibonacci_iterator));
	s.push_back(CUTE(test_postfix_incrementing_default_fibonacci_iterator_increments_this_fibonacci_iterator));
	s.push_back(CUTE(test_postfix_incrementing_default_fibonacci_iterator_returns_previous_value_fibonacci_iterator));
	s.push_back(CUTE(test_postfix_incrementing_default_fibonacci_iterator_returns_new_fibonacci_iterator));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}

