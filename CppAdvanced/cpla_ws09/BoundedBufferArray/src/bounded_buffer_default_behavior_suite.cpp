#include "bounded_buffer_default_behavior_suite.h"
#include "cute.h"
#include "BoundedBuffer.h"
#include <boost/type_index.hpp>


void test_int_buffer_of_capacity_thousand_is_empty() {
	BoundedBuffer<int, 1000> const buffer{};
	ASSERTM("New buffer should be empty", buffer.empty());
}

void test_buffer_constructor_for_capacity_zero_throws() {
	BoundedBuffer<int, 0> const buffer{};
	ASSERTM("New buffer should be empty", buffer.empty());
}

void test_const_int_buffer_of_capacity_thousand_is_not_full() {
	BoundedBuffer<int, 1000> const buffer{};
	ASSERTM("New buffer should not be full", !buffer.full());
}

void test_default_constructed_const_int_buffer_of_size_zero_is_full() {
	BoundedBuffer<int, 0> const buffer{};
	ASSERTM("New buffer of size 0 should be full", buffer.full());
}

void test_int_buffer_of_capacity_thousand_has_size_zero() {
	BoundedBuffer<int, 1000> const buffer{};
	ASSERT_EQUALM("New buffer should be empty", 0, buffer.size());
}

void test_default_constructed_const_int_buffer_of_size_zero_has_size_zero() {
	BoundedBuffer<int, 0> const buffer{};
	ASSERT_EQUALM("New buffer should be empty", 0, buffer.size());
}

void test_empty_bounded_buffer_throws_on_front() {
	BoundedBuffer<int, 23> buffer{};
	ASSERT_THROWS(buffer.front(), std::logic_error);
}

void test_empty_const_bounded_buffer_throws_on_front() {
	BoundedBuffer<int, 23> const buffer{};
	ASSERT_THROWS(buffer.front(), std::logic_error);
}

void test_empty_bounded_buffer_throws_on_back() {
	BoundedBuffer<int, 23> buffer{};
	ASSERT_THROWS(buffer.back(), std::logic_error);
}

void test_empty_const_bounded_buffer_throws_on_back() {
	BoundedBuffer<int, 23> const buffer{};
	ASSERT_THROWS(buffer.back(), std::logic_error);
}

void test_empty_bounded_buffer_throws_on_pop() {
	BoundedBuffer<int, 23> buffer{};
	ASSERT_THROWS(buffer.pop(), std::logic_error);
}

void test_full_bounded_buffer_throws_on_push_const_lvalue() {
	BoundedBuffer<int, 0> buffer{};
	int const lvalue{23};
	ASSERT_THROWS(buffer.push(lvalue), std::logic_error);
}

void test_full_bounded_buffer_throws_on_push_rvalue() {
	BoundedBuffer<int, 0> buffer{};
	ASSERT_THROWS(buffer.push(23), std::logic_error);
}

cute::suite make_suite_bounded_buffer_default_behavior_suite(){
	cute::suite s{};
	s.push_back(CUTE(test_int_buffer_of_capacity_thousand_is_empty));
	s.push_back(CUTE(test_buffer_constructor_for_capacity_zero_throws));
	s.push_back(CUTE(test_const_int_buffer_of_capacity_thousand_is_not_full));
	s.push_back(CUTE(test_default_constructed_const_int_buffer_of_size_zero_is_full));
	s.push_back(CUTE(test_int_buffer_of_capacity_thousand_has_size_zero));
	s.push_back(CUTE(test_default_constructed_const_int_buffer_of_size_zero_has_size_zero));
	s.push_back(CUTE(test_empty_bounded_buffer_throws_on_front));
	s.push_back(CUTE(test_empty_const_bounded_buffer_throws_on_front));
	s.push_back(CUTE(test_empty_bounded_buffer_throws_on_back));
	s.push_back(CUTE(test_empty_const_bounded_buffer_throws_on_back));
	s.push_back(CUTE(test_empty_bounded_buffer_throws_on_pop));
	s.push_back(CUTE(test_full_bounded_buffer_throws_on_push_const_lvalue));
	s.push_back(CUTE(test_full_bounded_buffer_throws_on_push_rvalue));
	return s;
}



