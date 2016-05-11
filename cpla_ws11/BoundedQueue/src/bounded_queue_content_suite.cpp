#include "bounded_queue_content_suite.h"

#include "cute.h"
#include "BoundedQueue.h"
#include "times_literal.hpp"
#include <stdexcept>


using namespace times::literal;

void test_queue_is_not_empty_after_push_rvalue() {
	BoundedQueue<int> queue { 5 };
	queue.push(5);
	ASSERTM("Queue should not be empty after push", !queue.empty());
}

void test_queue_is_not_empty_after_push_lvalue() {
	BoundedQueue<int> queue { 5 };
	int const lvalue { 5 };
	queue.push(lvalue);
	ASSERTM("Queue should not be empty after push", !queue.empty());
}

void test_queue_is_empty_after_one_push_and_pop() {
	BoundedQueue<int> queue { 5 };
	queue.push(5);
	queue.pop();
	ASSERTM("Queue should be empty after one push and pop", queue.empty());
}

void test_queue_of_size_two_is_full_after_two_pushs() {
	BoundedQueue<int> queue { 2 };
	2_times([&]() {queue.push(5);});
	ASSERTM("Queue of size two should be full after two pushs", queue.full());
}

void test_queue_size_is_one_after_push() {
	BoundedQueue<int> queue { 2 };
	queue.push(1);
	ASSERT_EQUAL(1, queue.size());
}

void test_queue_size_is_fifty_after_fifty_pushs() {
	BoundedQueue<int> queue { 75 };
	50_times([&]() {queue.push(5);});
	ASSERT_EQUAL(50, queue.size());
}



void test_queue_pop_gets_first_element_of_pushs() {
	BoundedQueue<int> queue { 5 };
	queue.push(1);
	queue.push(2);
	ASSERT_EQUAL(1, queue.pop());
}


void test_queue_pop_in_sequence_of_push() {
	BoundedQueue<int> queue { 5 };
	std::vector<int> frontValues { }, expectedValues { 1, 2, 3, 4, 5 };
	queue.push(1);
	queue.push(2);
	frontValues.push_back(queue.pop());
	queue.push(3);
	queue.push(4);
	frontValues.push_back(queue.pop());
	frontValues.push_back(queue.pop());
	queue.push(5);
	frontValues.push_back(queue.pop());
	frontValues.push_back(queue.pop());
	ASSERT_EQUAL(expectedValues, frontValues);
}

void test_queue_wrap_around_behavior_pop() {
	BoundedQueue<int> queue { 3 };
	std::vector<int> frontValues { }, expectedValues { 1, 2, 3,  4, 5, 6, 7 };
	queue.push(1);
	queue.push(2);
	frontValues.push_back(queue.pop());
	frontValues.push_back(queue.pop());
	queue.push(3);
	queue.push(4);
	queue.push(5);
	frontValues.push_back(queue.pop());
	frontValues.push_back(queue.pop());
	frontValues.push_back(queue.pop());
	queue.push(6);
	queue.push(7);
	frontValues.push_back(queue.pop());
	frontValues.push_back(queue.pop());
	ASSERT_EQUAL(expectedValues, frontValues);
}



void test_queue_after_swap_this_has_argument_content() {
	std::vector<int> frontValues { }, expectedValues { 1, 2, 3 };
	BoundedQueue<int> queue { 5 }, otherQueue { 5 };
	queue.push(1);
	queue.push(2);
	queue.push(3);
	otherQueue.swap(queue);
	3_times([&]() {frontValues.push_back(otherQueue.pop());});
	ASSERT_EQUAL(expectedValues, frontValues);
}

void test_queue_after_swap_argument_has_this_content() {
	std::vector<int> frontValues { }, expectedValues { 1, 2, 3 };
	BoundedQueue<int> queue { 5 }, otherQueue { 5 };
	queue.push(1);
	queue.push(2);
	queue.push(3);
	queue.swap(otherQueue);
	3_times([&]() {frontValues.push_back(otherQueue.pop()); });
	ASSERT_EQUAL(expectedValues, frontValues);
}

cute::suite make_suite_bounded_queue_content_suite() {
	cute::suite s;
	s.push_back(CUTE(test_queue_is_not_empty_after_push_rvalue));
	s.push_back(CUTE(test_queue_is_not_empty_after_push_lvalue));
	s.push_back(CUTE(test_queue_is_empty_after_one_push_and_pop));
	s.push_back(CUTE(test_queue_of_size_two_is_full_after_two_pushs));
	s.push_back(CUTE(test_queue_size_is_one_after_push));
	s.push_back(CUTE(test_queue_size_is_fifty_after_fifty_pushs));
	s.push_back(CUTE(test_queue_pop_gets_first_element_of_pushs));
	s.push_back(CUTE(test_queue_pop_in_sequence_of_push));
	s.push_back(CUTE(test_queue_wrap_around_behavior_pop));
	s.push_back(CUTE(test_queue_after_swap_this_has_argument_content));
	s.push_back(CUTE(test_queue_after_swap_argument_has_this_content));
	return s;
}

