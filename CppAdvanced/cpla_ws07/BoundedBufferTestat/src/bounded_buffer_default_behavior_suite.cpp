#include "bounded_buffer_default_behavior_suite.h"
#include "cute.h"
#include "BoundedBuffer.h"
#include <boost/type_index.hpp>


void test_buffer_constructor_for_capacity_zero_throws() {
	ASSERT_THROWS(BoundedBuffer<int> buffer{0}, std::invalid_argument);
}

void test_int_buffer_of_capacity_thousand_is_empty() {
	BoundedBuffer<int> const buffer{1000};
	ASSERTM("New buffer should be empty", buffer.empty());
}

void test_const_int_buffer_of_capacity_thousand_is_not_full() {
	BoundedBuffer<int> const buffer{1000};
	ASSERTM("New buffer should not be full", !buffer.full());
}

void test_int_buffer_of_capacity_thousand_has_size_zero() {
	BoundedBuffer<int> const buffer{1000};
	ASSERT_EQUALM("New buffer should be empty", 0, buffer.size());
}

void test_empty_bounded_buffer_throws_on_front() {
	BoundedBuffer<int> buffer{23};
	ASSERT_THROWS(buffer.front(), std::logic_error);
}

void test_empty_const_bounded_buffer_throws_on_front() {
	BoundedBuffer<int> const buffer{23};
	ASSERT_THROWS(buffer.front(), std::logic_error);
}

void test_empty_bounded_buffer_throws_on_back() {
	BoundedBuffer<int> buffer{23};
	ASSERT_THROWS(buffer.back(), std::logic_error);
}

void test_empty_const_bounded_buffer_throws_on_back() {
	BoundedBuffer<int> const buffer{23};
	ASSERT_THROWS(buffer.back(), std::logic_error);
}

void test_empty_bounded_buffer_throws_on_pop() {
	BoundedBuffer<int> buffer{23};
	ASSERT_THROWS(buffer.pop(), std::logic_error);
}

void test_full_bounded_buffer_throws_on_push_const_lvalue() {
	BoundedBuffer<int> buffer{1};
	int const lvalue{23};
	buffer.push(lvalue);
	ASSERT_THROWS(buffer.push(lvalue), std::logic_error);
}

void test_full_bounded_buffer_throws_on_push_rvalue() {
	BoundedBuffer<int> buffer{1};
	int const lvalue{23};
	buffer.push(lvalue);
	ASSERT_THROWS(buffer.push(23), std::logic_error);
}

cute::suite make_suite_bounded_buffer_default_behavior_suite(){
	cute::suite s{};
	s.push_back(CUTE(test_int_buffer_of_capacity_thousand_is_empty));
	s.push_back(CUTE(test_buffer_constructor_for_capacity_zero_throws));
	s.push_back(CUTE(test_const_int_buffer_of_capacity_thousand_is_not_full));
	s.push_back(CUTE(test_int_buffer_of_capacity_thousand_has_size_zero));
	s.push_back(CUTE(test_empty_bounded_buffer_throws_on_front));
	s.push_back(CUTE(test_empty_const_bounded_buffer_throws_on_front));
	s.push_back(CUTE(test_empty_bounded_buffer_throws_on_back));
	s.push_back(CUTE(test_empty_const_bounded_buffer_throws_on_back));
	s.push_back(CUTE(test_empty_bounded_buffer_throws_on_pop));
	s.push_back(CUTE(test_full_bounded_buffer_throws_on_push_const_lvalue));
	s.push_back(CUTE(test_full_bounded_buffer_throws_on_push_rvalue));
	return s;
}



