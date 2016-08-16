#include "bounded_queue_signatures_suite.h"

#include "cute.h"
#include "BoundedQueue.h"
#include <boost/type_index.hpp>
#include <chrono>


void test_bounded_queue_value_type_is_value() {
	auto value_type = boost::typeindex::type_id_with_cvr<BoundedQueue<int>::value_type>();
	auto expected_type = boost::typeindex::type_id_with_cvr<int>();
	ASSERT_EQUAL(expected_type.pretty_name(), value_type.pretty_name());
}

void test_bounded_queue_reference_type_is_reference() {
	auto reference_type = boost::typeindex::type_id_with_cvr<BoundedQueue<int>::reference>();
	auto expected_type = boost::typeindex::type_id_with_cvr<int &>();
	ASSERT_EQUAL(expected_type.pretty_name(), reference_type.pretty_name());
}

void test_bounded_queue_const_reference_type_is_const_reference() {
	auto const_reference_type = boost::typeindex::type_id_with_cvr<BoundedQueue<int>::const_reference>();
	auto expected_type = boost::typeindex::type_id_with_cvr<int const &>();
	ASSERT_EQUAL(expected_type.pretty_name(), const_reference_type.pretty_name());
}

void test_bounded_queue_size_type_is_size_t() {
	auto size_type = boost::typeindex::type_id_with_cvr<BoundedQueue<int>::size_type>();
	auto expected_type = boost::typeindex::type_id_with_cvr<size_t>();
	ASSERT_EQUAL(expected_type.pretty_name(), size_type.pretty_name());
}

void test_const_bounded_queue_type_of_empty_is_bool() {
	BoundedQueue<int> const queue { 15 };
	auto empty_type = boost::typeindex::type_id_with_cvr<decltype(queue.empty())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
	ASSERT_EQUAL(expected_type.pretty_name(), empty_type.pretty_name());
}

void test_const_bounded_queue_type_of_full_is_bool() {
	BoundedQueue<int> const queue { 15 };
	auto full_type = boost::typeindex::type_id_with_cvr<decltype(queue.full())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
	ASSERT_EQUAL(expected_type.pretty_name(), full_type.pretty_name());
}

void test_const_bounded_queue_type_of_size_is_size_t() {
	BoundedQueue<int> const queue { 15 };
	auto size_type = boost::typeindex::type_id_with_cvr<decltype(queue.size())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<size_t>();
	ASSERT_EQUAL(expected_type.pretty_name(), size_type.pretty_name());
}

void test_bounded_queue_type_of_push_of_const_lvalue_is_void() {
	BoundedQueue<int> queue { 15 };
	int const lvalue { 23 };
	auto push_type = boost::typeindex::type_id_with_cvr<decltype(queue.push(lvalue))>();
	auto expected_type = boost::typeindex::type_id_with_cvr<void>();
	ASSERT_EQUAL(expected_type.pretty_name(), push_type.pretty_name());
}

void test_bounded_queue_type_of_push_of_rvalue_is_void() {
	BoundedQueue<int> queue { 15 };
	auto push_type = boost::typeindex::type_id_with_cvr<decltype(queue.push(23))>();
	auto expected_type = boost::typeindex::type_id_with_cvr<void>();
	ASSERT_EQUAL(expected_type.pretty_name(), push_type.pretty_name());
}

void test_bounded_queue_type_of_try_push_of_const_lvalue_is_bool() {
	BoundedQueue<int> queue { 15 };
	int const lvalue { 23 };
	auto push_type = boost::typeindex::type_id_with_cvr<decltype(queue.try_push(lvalue))>();
	auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
	ASSERT_EQUAL(expected_type.pretty_name(), push_type.pretty_name());
}

void test_bounded_queue_type_of_try_push_of_rvalue_is_bool() {
	BoundedQueue<int> queue { 15 };
	auto push_type = boost::typeindex::type_id_with_cvr<decltype(queue.try_push(23))>();
	auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
	ASSERT_EQUAL(expected_type.pretty_name(), push_type.pretty_name());
}

void test_bounded_queue_type_of_pop_is_value_type() {
	BoundedQueue<int> queue { 15 };
	auto pop_type = boost::typeindex::type_id_with_cvr<decltype(queue.pop())>();
	auto expected_type = boost::typeindex::type_id_with_cvr<int>();
	ASSERT_EQUAL(expected_type.pretty_name(), pop_type.pretty_name());
}

void test_bounded_queue_type_of_try_pop_is_bool() {
	BoundedQueue<int> queue { 15 };
	int popped_value { };
	auto pop_type = boost::typeindex::type_id_with_cvr<decltype(queue.try_pop(popped_value))>();
	auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
	ASSERT_EQUAL(expected_type.pretty_name(), pop_type.pretty_name());
}

void test_bounded_queue_type_of_swap_is_void() {
	BoundedQueue<int> queue { 15 }, other_queue { 15 };
	auto pop_type = boost::typeindex::type_id_with_cvr<decltype(queue.swap(other_queue))>();
	auto expected_type = boost::typeindex::type_id_with_cvr<void>();
	ASSERT_EQUAL(expected_type.pretty_name(), pop_type.pretty_name());
}

void test_bounded_queue_type_of_try_push_for_is_bool() {
	BoundedQueue<int> queue { 15 };
	auto pop_type = boost::typeindex::type_id_with_cvr<decltype(queue.try_push_for(1, std::chrono::seconds{1}))>();
	auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
	ASSERT_EQUAL(expected_type.pretty_name(), pop_type.pretty_name());
}

void test_bounded_queue_type_of_try_pop_for_is_bool() {
	BoundedQueue<int> queue { 15 };
	int result{};
	auto pop_type = boost::typeindex::type_id_with_cvr<decltype(queue.try_pop_for(result, std::chrono::seconds{1}))>();
	auto expected_type = boost::typeindex::type_id_with_cvr<bool>();
	ASSERT_EQUAL(expected_type.pretty_name(), pop_type.pretty_name());
}

cute::suite make_suite_bounded_queue_signatures_suite() {
	cute::suite s;
	s.push_back(CUTE(test_bounded_queue_value_type_is_value));
	s.push_back(CUTE(test_bounded_queue_reference_type_is_reference));
	s.push_back(CUTE(test_bounded_queue_const_reference_type_is_const_reference));
	s.push_back(CUTE(test_bounded_queue_size_type_is_size_t));
	s.push_back(CUTE(test_const_bounded_queue_type_of_empty_is_bool));
	s.push_back(CUTE(test_const_bounded_queue_type_of_full_is_bool));
	s.push_back(CUTE(test_const_bounded_queue_type_of_size_is_size_t));
	s.push_back(CUTE(test_bounded_queue_type_of_push_of_const_lvalue_is_void));
	s.push_back(CUTE(test_bounded_queue_type_of_push_of_rvalue_is_void));
	s.push_back(CUTE(test_bounded_queue_type_of_pop_is_value_type));
	s.push_back(CUTE(test_bounded_queue_type_of_swap_is_void));
	s.push_back(CUTE(test_bounded_queue_type_of_try_push_of_const_lvalue_is_bool));
	s.push_back(CUTE(test_bounded_queue_type_of_try_push_of_rvalue_is_bool));
	s.push_back(CUTE(test_bounded_queue_type_of_try_pop_is_bool));
	s.push_back(CUTE(test_bounded_queue_type_of_try_push_for_is_bool));
	s.push_back(CUTE(test_bounded_queue_type_of_try_pop_for_is_bool));
	return s;
}

