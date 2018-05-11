#include "bounded_buffer_iterator_suite.h"
#include "BoundedBuffer.h"
#include "cute.h"
#include "n_times.h"


using namespace cpp_advanced::times_literal;

void test_begin_and_end_of_empty_buffer_are_equal() {
	BoundedBuffer<int> buffer{5};
	auto begin = buffer.begin();
	auto end = buffer.end();
	ASSERT_EQUAL(begin, end);
}

void test_begin_and_end_of_non_empty_buffer_are_inequal() {
	BoundedBuffer<int> buffer{5};
	buffer.push(23);
	auto begin = buffer.begin();
	auto end = buffer.end();
	ASSERT_NOT_EQUAL_TO(begin, end);
}

void test_begin_and_end_of_full_buffer_are_inequal() {
	BoundedBuffer<int> buffer{5};
	5_times([&](){buffer.push(23);});
	auto begin = buffer.begin();
	auto end = buffer.end();
	ASSERT_NOT_EQUAL_TO(begin, end);
}

BoundedBuffer<int> createBufferWithFiveConsecutiveInts(int startValue) {
	BoundedBuffer<int> buffer{5};
	auto i = startValue;
	5_times([& /*, i = 0 */]() {buffer.push(i++);});
	return buffer;
}

void test_two_begins_of_same_buffer_are_equal() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};

	ASSERT_EQUAL(buffer.begin(), buffer.begin());
}

void test_two_ends_of_same_buffer_are_equal() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};

	ASSERT_EQUAL(buffer.end(), buffer.end());
}

void test_two_begins_of_same_const_buffer_are_equal() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};

	ASSERT_EQUAL(buffer.begin(), buffer.begin());
}

void test_two_ends_of_same_const_buffer_are_equal() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};

	ASSERT_EQUAL(buffer.end(), buffer.end());
}

void test_two_cbegins_of_same_const_buffer_are_equal() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};

	ASSERT_EQUAL(buffer.cbegin(), buffer.cbegin());
}

void test_two_cends_of_same_const_buffer_are_equal() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};

	ASSERT_EQUAL(buffer.cend(), buffer.cend());
}

void test_begin_points_to_the_correct_element() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};

	ASSERT_EQUAL(15, *buffer.begin());
}

void test_prefix_incremented_begin_points_to_the_correct_element() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	BoundedBuffer<int>::const_iterator iterator = buffer.begin();

	++iterator;

	ASSERT_EQUAL(16, *iterator);
}

void test_expression_of_prefix_incremented_begin_points_to_the_correct_element() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.begin();

	ASSERT_EQUAL(16, *(++iterator));
}

void test_twice_prefix_incremented_begin_points_to_the_correct_element() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.begin();

	2_times([&](){++iterator;});

	ASSERT_EQUAL(17, *iterator);
}

void test_postfix_incremented_begin_points_to_the_correct_element() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.begin();

	iterator++;

	ASSERT_EQUAL(16, *iterator);
}

void test_expression_of_postfix_incremented_begin_points_to_the_correct_element() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.begin();

	ASSERT_EQUAL(15, *(iterator++));
}

void test_iterator_prefix_incremented_to_the_end_equals_end() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.begin();

	5_times([&](){++iterator;});

	ASSERT_EQUAL(buffer.end(), iterator);
}

void test_iterator_incremented_wrap_around_leads_to_equal_end() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
	3_times([&](){buffer.pop();});
	buffer.push(20);
	buffer.push(21);
	auto iterator = buffer.begin();

	4_times([&](){++iterator;});

	ASSERT_EQUAL(buffer.end(), iterator);
}

void test_prefix_incrementing_end_iterator_throws() {
	BoundedBuffer<int> buffer{5};
	auto iterator = buffer.end();
	ASSERT_THROWS(++iterator, std::logic_error);
}

void test_postfix_incrementing_end_iterator_throws() {
	BoundedBuffer<int> buffer{5};
	auto iterator = buffer.end();
	ASSERT_THROWS(iterator++, std::logic_error);
}

void test_plus_expression_for_iterator() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.begin();

	ASSERT_EQUAL(17, *(iterator + 2));
}

void test_plus_assign_expression_for_iterator() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.begin();

	iterator += 3;

	ASSERT_EQUAL(18, *iterator);
}

void test_plus_beyond_end_throws() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.end();

	ASSERT_THROWS(iterator + 6, std::logic_error);
}

void test_plus_assign_beyond_end_throws() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.end();

	ASSERT_THROWS(iterator += 6, std::logic_error);
}

void test_minus_expression_for_iterator() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.end();

	ASSERT_EQUAL(18, *(iterator - 2));
}

void test_minus_assign_expression_for_iterator() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.end();

	iterator -= 3;

	ASSERT_EQUAL(17, *iterator);
}

void test_minus_beyond_begin_throws() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.end();

	ASSERT_THROWS(iterator - 6, std::logic_error);
}

void test_minus_assign_beyond_begin_throws() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.end();

	ASSERT_THROWS(iterator -= 6, std::logic_error);
}

void test_accessing_element_at_end_throws() {
	BoundedBuffer<int> buffer{5};
	auto iterator = buffer.end();
	ASSERT_THROWS(*iterator, std::logic_error);
}

void test_postfix_decrementing_on_empty_buffer_begin_throws() {
	BoundedBuffer<int> buffer{5};
	auto iterator = buffer.begin();
	ASSERT_THROWS(iterator--, std::logic_error);
}

void test_prefix_decrementing_on_empty_buffer_begin_throws() {
	BoundedBuffer<int> buffer{5};
	auto iterator = buffer.begin();
	ASSERT_THROWS(--iterator, std::logic_error);
}

void test_postfix_decrementing_on_non_empty_buffer_begin_throws() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.begin();
	ASSERT_THROWS(iterator--, std::logic_error);
}

void test_prefix_decrementing_on_non_empty_buffer_begin_throws() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.begin();
	ASSERT_THROWS(--iterator, std::logic_error);
}

void test_postfix_decremented_end_points_to_last_element() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.end();

	iterator--;

	ASSERT_EQUAL(19, *iterator);
}

void test_prefix_decremented_end_points_to_last_element() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
	auto iterator = buffer.end();

	--iterator;

	ASSERT_EQUAL(19, *iterator);
}

void test_begin_end_ranges_of_the_same_buffer_are_equal() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};
	ASSERT(std::equal(buffer.begin(), buffer.end(), buffer.begin()));
}

void test_begin_end_ranges_of_buffers_with_the_same_elements_are_equal() {
	BoundedBuffer<int> const buffer{createBufferWithFiveConsecutiveInts(0)};
	BoundedBuffer<int> const buffer2{createBufferWithFiveConsecutiveInts(0)};
	ASSERT(std::equal(buffer.begin(), buffer.end(), buffer2.begin()));
}

void test_difference_on_different_buffers_throws() {
	BoundedBuffer<int> buffer{5}, buffer2{5};
	ASSERT_THROWS(buffer.begin() - buffer2.begin(), std::logic_error);
}

void test_difference_between_begin_and_end_on_empty_buffer() {
	BoundedBuffer<int> buffer{5};
	std::ptrdiff_t distance = buffer.end() - buffer.begin();
	ASSERT_EQUAL(0, distance);
}

void test_difference_between_begin_and_end_on_buffer_with_some_elements() {
	BoundedBuffer<int> buffer{5};
	3_times([&](){buffer.push(27);});
	std::ptrdiff_t distance = buffer.end() - buffer.begin();
	ASSERT_EQUAL(3, distance);
}

void test_difference_between_begin_and_end_on_buffer_with_some_elements_wrapped_around() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
	3_times([&](){buffer.pop();});
	buffer.push(20);
	buffer.push(21);

	std::ptrdiff_t distance = buffer.end() - buffer.begin();

	ASSERT_EQUAL(4, distance);
}

void test_difference_between_arbitrary_iterators_on_buffer_with_some_elements_wrapped_around() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(15)};
	3_times([&](){buffer.pop();});
	buffer.push(20);
	buffer.push(21);
	auto begin = buffer.begin();
	auto end = buffer.end();

	begin++;
	end--;
	std::ptrdiff_t distance = end - begin;

	ASSERT_EQUAL(2, distance);
}

void test_difference_between_begin_and_end_on_full_buffer() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
	std::ptrdiff_t distance = buffer.end() - buffer.begin();
	ASSERT_EQUAL(5, distance);
}

void test_begin_end_ranges_of_buffers_with_the_same_elements_but_not_at_the_same_location_are_equal() {
	BoundedBuffer<int> buffer{5};
	3_times([&](){buffer.push(23); buffer.pop();});
	auto i = 0;
	5_times([&]() {buffer.push(i++);});
	BoundedBuffer<int> const buffer2{createBufferWithFiveConsecutiveInts(0)};
	ASSERT(std::equal(buffer.begin(), buffer.end(), buffer2.begin(), buffer2.end()));
}

void test_begin_is_smaller_than_end_for_non_empty_buffers() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
	ASSERT_LESS(buffer.begin(), buffer.end());
}

void test_begin_is_greater_than_end_for_non_empty_buffers() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
	ASSERT_GREATER(buffer.end(), buffer.begin());
}

void test_arbitrary_iterators_compare_less_than_for_non_empty_buffers() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
	auto lower = buffer.begin();
	auto greater = buffer.end();

	lower++;
	greater--;

	ASSERT_LESS(lower, greater);
}

void test_arbitrary_iterators_compare_greater_than_for_non_empty_buffers() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
	auto lower = buffer.begin();
	auto greater = buffer.end();

	lower++;
	greater--;

	ASSERT_GREATER(greater, lower);
}


void test_relative_comparison_of_iterators_to_different_buffers_throws() {
	BoundedBuffer<int> buffer{5}, buffer2{5};

	ASSERT_THROWS(buffer.begin() < buffer2.begin(), std::logic_error);
}

void test_non_const_begin_iterator_overwrites_element() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
	*buffer.begin() = 23;
	ASSERT_EQUAL(23, buffer.front());
}

void test_non_const_end_iterator_overwrites_element() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
	BoundedBuffer<int>::iterator iterator = buffer.end();
	*(--iterator) = 23;
	ASSERT_EQUAL(23, buffer.back());
}

void test_index_operator() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
	ASSERT_EQUAL(2, buffer.begin()[2]);
}

void test_index_end_minus_one_operator() {
	BoundedBuffer<int> buffer{createBufferWithFiveConsecutiveInts(0)};
	ASSERT_EQUAL(buffer.back(), buffer.end()[-1]);
}

struct TypeWithMember {
	int value;
};

void test_arrow_operator() {
	BoundedBuffer<TypeWithMember> buffer{5};

	buffer.push(TypeWithMember{23});

	ASSERT_EQUAL(23, buffer.begin()->value);
}

cute::suite make_suite_bounded_buffer_iterator_suite(){
	cute::suite s;
	s.push_back(CUTE(test_begin_and_end_of_empty_buffer_are_equal));
	s.push_back(CUTE(test_begin_and_end_of_non_empty_buffer_are_inequal));
	s.push_back(CUTE(test_begin_and_end_of_full_buffer_are_inequal));
	s.push_back(CUTE(test_two_begins_of_same_buffer_are_equal));
	s.push_back(CUTE(test_two_ends_of_same_buffer_are_equal));
	s.push_back(CUTE(test_two_begins_of_same_const_buffer_are_equal));
	s.push_back(CUTE(test_two_ends_of_same_const_buffer_are_equal));
	s.push_back(CUTE(test_two_cbegins_of_same_const_buffer_are_equal));
	s.push_back(CUTE(test_two_cends_of_same_const_buffer_are_equal));
	s.push_back(CUTE(test_begin_points_to_the_correct_element));
	s.push_back(CUTE(test_prefix_incremented_begin_points_to_the_correct_element));
	s.push_back(CUTE(test_twice_prefix_incremented_begin_points_to_the_correct_element));
	s.push_back(CUTE(test_iterator_prefix_incremented_to_the_end_equals_end));
	s.push_back(CUTE(test_iterator_incremented_wrap_around_leads_to_equal_end));
	s.push_back(CUTE(test_prefix_incrementing_end_iterator_throws));
	s.push_back(CUTE(test_postfix_incrementing_end_iterator_throws));
	s.push_back(CUTE(test_accessing_element_at_end_throws));
	s.push_back(CUTE(test_expression_of_prefix_incremented_begin_points_to_the_correct_element));
	s.push_back(CUTE(test_postfix_incremented_begin_points_to_the_correct_element));
	s.push_back(CUTE(test_expression_of_postfix_incremented_begin_points_to_the_correct_element));
	s.push_back(CUTE(test_postfix_decrementing_on_empty_buffer_begin_throws));
	s.push_back(CUTE(test_prefix_decrementing_on_empty_buffer_begin_throws));
	s.push_back(CUTE(test_postfix_decremented_end_points_to_last_element));
	s.push_back(CUTE(test_prefix_decremented_end_points_to_last_element));
	s.push_back(CUTE(test_postfix_decrementing_on_non_empty_buffer_begin_throws));
	s.push_back(CUTE(test_prefix_decrementing_on_non_empty_buffer_begin_throws));
	s.push_back(CUTE(test_begin_end_ranges_of_the_same_buffer_are_equal));
	s.push_back(CUTE(test_begin_end_ranges_of_buffers_with_the_same_elements_are_equal));
	s.push_back(CUTE(test_difference_on_different_buffers_throws));
	s.push_back(CUTE(test_difference_between_begin_and_end_on_empty_buffer));
	s.push_back(CUTE(test_difference_between_begin_and_end_on_buffer_with_some_elements));
	s.push_back(CUTE(test_difference_between_begin_and_end_on_full_buffer));
	s.push_back(CUTE(test_difference_between_begin_and_end_on_buffer_with_some_elements_wrapped_around));
	s.push_back(CUTE(test_difference_between_arbitrary_iterators_on_buffer_with_some_elements_wrapped_around));
	s.push_back(CUTE(test_begin_end_ranges_of_buffers_with_the_same_elements_but_not_at_the_same_location_are_equal));
	s.push_back(CUTE(test_plus_expression_for_iterator));
	s.push_back(CUTE(test_plus_assign_expression_for_iterator));
	s.push_back(CUTE(test_minus_expression_for_iterator));
	s.push_back(CUTE(test_minus_assign_expression_for_iterator));
	s.push_back(CUTE(test_plus_beyond_end_throws));
	s.push_back(CUTE(test_plus_assign_beyond_end_throws));
	s.push_back(CUTE(test_minus_beyond_begin_throws));
	s.push_back(CUTE(test_minus_assign_beyond_begin_throws));
	s.push_back(CUTE(test_begin_is_smaller_than_end_for_non_empty_buffers));
	s.push_back(CUTE(test_begin_is_greater_than_end_for_non_empty_buffers));
	s.push_back(CUTE(test_arbitrary_iterators_compare_less_than_for_non_empty_buffers));
	s.push_back(CUTE(test_arbitrary_iterators_compare_greater_than_for_non_empty_buffers));
	s.push_back(CUTE(test_relative_comparison_of_iterators_to_different_buffers_throws));
	s.push_back(CUTE(test_non_const_begin_iterator_overwrites_element));
	s.push_back(CUTE(test_non_const_end_iterator_overwrites_element));
	s.push_back(CUTE(test_index_operator));
	s.push_back(CUTE(test_index_end_minus_one_operator));
	s.push_back(CUTE(test_arrow_operator));
	return s;
}



