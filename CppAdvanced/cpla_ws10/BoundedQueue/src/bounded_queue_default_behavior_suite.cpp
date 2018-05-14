#include "bounded_queue_default_behavior_suite.h"

#include "cute.h"
#include "BoundedQueue.h"
#include <boost/type_index.hpp>


void test_queue_constructor_for_capacity_zero_throws() {
	ASSERT_THROWS(BoundedQueue<int> queue{0}, std::invalid_argument);
}

void test_int_queue_of_capacity_thousand_is_empty() {
	BoundedQueue<int> const queue{1000};
	ASSERTM("New queue should be empty", queue.empty());
}

void test_const_int_queue_of_capacity_thousand_is_not_full() {
	BoundedQueue<int> const queue{1000};
	ASSERTM("New queue should not be full", !queue.full());
}

void test_int_queue_of_capacity_thousand_has_size_zero() {
	BoundedQueue<int> const queue{1000};
	ASSERT_EQUALM("New queue should be empty", 0, queue.size());
}


void test_empty_bounded_queue_returns_false_on_try_pop() {
	BoundedQueue<int> queue{23};
	auto val=queue.try_pop(); // assume std::optional<int>
	static_assert(std::is_same_v<decltype(val),std::optional<int>>,"must return an optional");
	ASSERT(!val);
}

void test_full_bounded_queue_returns_false_on_try_push_const_lvalue() {
	BoundedQueue<int> queue{1};
	int const lvalue{23};
	queue.push(lvalue);
	ASSERT(!queue.try_push(lvalue));
}

cute::suite make_suite_bounded_queue_default_behavior_suite(){
	cute::suite s{};
	s.push_back(CUTE(test_int_queue_of_capacity_thousand_is_empty));
	s.push_back(CUTE(test_queue_constructor_for_capacity_zero_throws));
	s.push_back(CUTE(test_const_int_queue_of_capacity_thousand_is_not_full));
	s.push_back(CUTE(test_int_queue_of_capacity_thousand_has_size_zero));
	s.push_back(CUTE(test_empty_bounded_queue_returns_false_on_try_pop));
	s.push_back(CUTE(test_full_bounded_queue_returns_false_on_try_push_const_lvalue));
	return s;
}



