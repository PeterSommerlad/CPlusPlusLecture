#include "bounded_buffer_signatures_suite.h"
#include "cute.h"
#include "BoundedBuffer.h"
#include <boost/type_index.hpp>


void test_bounded_buffer_value_type_is_value() {
	auto value_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int>::value_type>();
	auto expected_type = boost::typeindex::type_id_with_cvr<int>();
	ASSERT_EQUAL(expected_type.pretty_name(), value_type.pretty_name());
}

void test_bounded_buffer_reference_type_is_reference() {
	auto reference_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int>::reference>();
	auto expected_type = boost::typeindex::type_id_with_cvr<int &>();
	ASSERT_EQUAL(expected_type.pretty_name(), reference_type.pretty_name());
}

void test_bounded_buffer_const_reference_type_is_const_reference() {
	auto const_reference_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int>::const_reference>();
	auto expected_type = boost::typeindex::type_id_with_cvr<int const &>();
	ASSERT_EQUAL(expected_type.pretty_name(), const_reference_type.pretty_name());
}

void test_bounded_buffer_size_type_is_size_t() {
	auto size_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int>::size_type>();
	auto expected_type = boost::typeindex::type_id_with_cvr<size_t>();
	ASSERT_EQUAL(expected_type.pretty_name(), size_type.pretty_name());
}


void test_const_bounded_buffer_type_of_empty_is_bool() {
	BoundedBuffer<int> const buffer{15};
	auto empty_type = boost::typeindex::type_id_with_cvr<decltype(buffer.empty())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
	ASSERT_EQUAL(expected_type.pretty_name(), empty_type.pretty_name());
}

void test_const_bounded_buffer_type_of_full_is_bool() {
	BoundedBuffer<int> const buffer{15};
	auto full_type = boost::typeindex::type_id_with_cvr<decltype(buffer.full())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
	ASSERT_EQUAL(expected_type.pretty_name(), full_type.pretty_name());
}

void test_bounded_buffer_front_type_is_reference_type() {
	BoundedBuffer<int> buffer{15};
	auto front_type = boost::typeindex::type_id_with_cvr<decltype(buffer.front())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int>::reference>();
	ASSERT_EQUAL(expected_type.pretty_name(), front_type.pretty_name());
}

void test_const_bounded_buffer_front_type_is_const_reference_type() {
	BoundedBuffer<int> const buffer{15};
	auto front_type = boost::typeindex::type_id_with_cvr<decltype(buffer.front())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int>::const_reference>();
	ASSERT_EQUAL(expected_type.pretty_name(), front_type.pretty_name());
}

void test_bounded_buffer_back_type_is_reference_type() {
	BoundedBuffer<int> buffer{15};
	auto back_type = boost::typeindex::type_id_with_cvr<decltype(buffer.back())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int>::reference>();
	ASSERT_EQUAL(expected_type.pretty_name(), back_type.pretty_name());
}

void test_const_bounded_buffer_back_type_is_reference_type() {
	BoundedBuffer<int> const buffer{15};
	auto back_type = boost::typeindex::type_id_with_cvr<decltype(buffer.back())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<BoundedBuffer<int>::const_reference>();
	ASSERT_EQUAL(expected_type.pretty_name(), back_type.pretty_name());
}

void test_bounded_buffer_pop_type_is_reference_type() {
	BoundedBuffer<int> buffer{15};
	auto pop_type = boost::typeindex::type_id_with_cvr<decltype(buffer.pop())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<void>();
	ASSERT_EQUAL(expected_type.pretty_name(), pop_type.pretty_name());
}

void test_const_bounded_buffer_type_of_size_is_size_t() {
	BoundedBuffer<int> const buffer{15};
	auto size_type = boost::typeindex::type_id_with_cvr<decltype(buffer.size())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<size_t>();
	ASSERT_EQUAL(expected_type.pretty_name(), size_type.pretty_name());
}

void test_bounded_buffer_type_of_push_of_const_lvalue_is_void() {
	BoundedBuffer<int> buffer{15};
	int const lvalue{23};
	auto push_type = boost::typeindex::type_id_with_cvr<decltype(buffer.push(lvalue))>();
	auto expected_type = boost::typeindex::type_id_with_cvr<void>();
	ASSERT_EQUAL(expected_type.pretty_name(), push_type.pretty_name());
}

void test_bounded_buffer_type_of_push_of_rvalue_is_void() {
	BoundedBuffer<int> buffer{15};
	auto push_type = boost::typeindex::type_id_with_cvr<decltype(buffer.push(23))>();
	auto expected_type = boost::typeindex::type_id_with_cvr<void>();
	ASSERT_EQUAL(expected_type.pretty_name(), push_type.pretty_name());
}

void test_bounded_buffer_type_of_pop_is_void() {
	BoundedBuffer<int> buffer{15};
	auto pop_type = boost::typeindex::type_id_with_cvr<decltype(buffer.pop())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<void>();
	ASSERT_EQUAL(expected_type.pretty_name(), pop_type.pretty_name());
}

void test_bounded_buffer_type_of_swap_is_void() {
	BoundedBuffer<int> buffer{15}, other_buffer{15};
	auto pop_type = boost::typeindex::type_id_with_cvr<decltype(buffer.swap(other_buffer))>();
	auto expected_type = boost::typeindex::type_id_with_cvr<void>();
	ASSERT_EQUAL(expected_type.pretty_name(), pop_type.pretty_name());
}


cute::suite make_suite_bounded_buffer_signatures_suite(){
	cute::suite s;
	s.push_back(CUTE(test_bounded_buffer_value_type_is_value));
	s.push_back(CUTE(test_bounded_buffer_reference_type_is_reference));
	s.push_back(CUTE(test_bounded_buffer_const_reference_type_is_const_reference));
	s.push_back(CUTE(test_bounded_buffer_size_type_is_size_t));
	s.push_back(CUTE(test_const_bounded_buffer_type_of_empty_is_bool));
	s.push_back(CUTE(test_const_bounded_buffer_type_of_full_is_bool));
	s.push_back(CUTE(test_bounded_buffer_front_type_is_reference_type));
	s.push_back(CUTE(test_bounded_buffer_back_type_is_reference_type));
	s.push_back(CUTE(test_const_bounded_buffer_back_type_is_reference_type));
	s.push_back(CUTE(test_bounded_buffer_pop_type_is_reference_type));
	s.push_back(CUTE(test_const_bounded_buffer_front_type_is_const_reference_type));
	s.push_back(CUTE(test_const_bounded_buffer_type_of_size_is_size_t));
	s.push_back(CUTE(test_bounded_buffer_type_of_push_of_const_lvalue_is_void));
	s.push_back(CUTE(test_bounded_buffer_type_of_push_of_rvalue_is_void));
	s.push_back(CUTE(test_bounded_buffer_type_of_pop_is_void));
	s.push_back(CUTE(test_bounded_buffer_type_of_swap_is_void));
	return s;
}



