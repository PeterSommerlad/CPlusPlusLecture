#include "bounded_queue_non_default_constructible_element_type_suite.h"

#include "cute.h"
#include "BoundedQueue.h"

struct NonDefaultConstructible {
	NonDefaultConstructible() = delete;

	NonDefaultConstructible(int) : value{INITIALIZED} {}

	~NonDefaultConstructible() {
		throwIfUninitialized();
		nOfDtorCalls++;
		value = 0;
	}

	NonDefaultConstructible(NonDefaultConstructible const & other) : value{other.value}{
		other.throwIfUninitialized();
		nOfCopyConstructions++;
	}

	NonDefaultConstructible& operator=(NonDefaultConstructible const & other) {
		throwIfUninitialized();
		other.throwIfUninitialized();
		nOfCopyAssignments++;
		return *this;
	}

	NonDefaultConstructible& operator=(NonDefaultConstructible && other) {
		throwIfUninitialized();
		other.throwIfUninitialized();
		nOfMoveAssignments++;
		return *this;
	}

	NonDefaultConstructible(NonDefaultConstructible && other) : value{INITIALIZED}{
		other.throwIfUninitialized();
		std::swap(value, other.value);
		nOfMoveConstructions++;
	}

	static unsigned nOfCopyConstructions;
	static unsigned nOfCopyAssignments;
	static unsigned nOfMoveConstructions;
	static unsigned nOfMoveAssignments;
	static unsigned nOfDtorCalls;
private:
	void throwIfUninitialized() const {
		if (value != 1234) {
			throw std::logic_error{"must not call operations on uninitialized NDC, with value: " + value};
		}
	}

	volatile unsigned value;
	static const unsigned INITIALIZED = 1234;
};

unsigned NonDefaultConstructible::nOfCopyConstructions{0};
unsigned NonDefaultConstructible::nOfCopyAssignments{0};
unsigned NonDefaultConstructible::nOfMoveConstructions{0};
unsigned NonDefaultConstructible::nOfMoveAssignments{0};
unsigned NonDefaultConstructible::nOfDtorCalls{0};

void resetCounters() {
	NonDefaultConstructible::nOfCopyConstructions = 0;
	NonDefaultConstructible::nOfCopyAssignments = 0;
	NonDefaultConstructible::nOfMoveConstructions = 0;
	NonDefaultConstructible::nOfMoveAssignments = 0;
	NonDefaultConstructible::nOfDtorCalls = 0;
}

void test_new_queue_of_nondefaultconstructible_invokes_no_destructors() {
	resetCounters();
	BoundedQueue<NonDefaultConstructible> queue{5};
	ASSERT_EQUAL(0, NonDefaultConstructible::nOfDtorCalls);
}

void test_element_in_queue_is_destroyed_once() {
	{
		BoundedQueue<NonDefaultConstructible> queue{5};
		queue.push(NonDefaultConstructible{23});
		resetCounters();
	}
	ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

void test_element_in_moved_queue_is_destroyed_once() {
	{
		BoundedQueue<NonDefaultConstructible> queue{5};
		queue.push(NonDefaultConstructible{23});
		resetCounters();

		BoundedQueue<NonDefaultConstructible> moved{std::move(queue)};
	}
	ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

void test_every_element_in_copied_queue_is_destroyed_once() {
	{
		BoundedQueue<NonDefaultConstructible> queue{5};
		queue.push(NonDefaultConstructible{23});
		resetCounters();

		BoundedQueue<NonDefaultConstructible> copy{queue};
	}
	ASSERT_EQUAL(2, NonDefaultConstructible::nOfDtorCalls);
}

void test_pop_destroys_element() {
	BoundedQueue<NonDefaultConstructible> queue{5};
	queue.push(NonDefaultConstructible{23});
	resetCounters();

	auto tmp=queue.pop();
	ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

void test_lvalue_push_copies_element() {
	resetCounters();
	BoundedQueue<NonDefaultConstructible> queue{5};
	NonDefaultConstructible element{23};

	queue.push(element);

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfCopyConstructions);
}

void test_rvalue_push_moves_element() {
	resetCounters();
	BoundedQueue<NonDefaultConstructible> queue{5};
	NonDefaultConstructible element{23};

	queue.push(std::move(element));

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfMoveConstructions);
}

void test_lvalue_push_must_not_copy_assign() {
	BoundedQueue<NonDefaultConstructible> queue{5};
	NonDefaultConstructible element{23};

	resetCounters();
	queue.push(element);

	ASSERT_EQUAL(0, NonDefaultConstructible::nOfCopyAssignments);
}

void test_rvalue_push_must_not_move_assign() {
	BoundedQueue<NonDefaultConstructible> queue{5};
	NonDefaultConstructible element{23};

	resetCounters();
	queue.push(std::move(element));

	ASSERT_EQUAL(0, NonDefaultConstructible::nOfMoveAssignments);
}

void test_self_copy_assignment_unchanged_size() {
	BoundedQueue<NonDefaultConstructible> queue{5};
	queue.push(NonDefaultConstructible{23});

	resetCounters();
	queue = (queue);

	ASSERT_EQUAL(1, queue.size());
}

void test_self_move_assignment_unchanged_size() {
	BoundedQueue<NonDefaultConstructible> queue{5};
	queue.push(NonDefaultConstructible{23});

	resetCounters();
	queue = std::move(queue);

	ASSERT_EQUAL(1, queue.size());
}

void test_self_copy_assignment_no_copy_construction() {
	BoundedQueue<NonDefaultConstructible> queue{5};
	queue.push(NonDefaultConstructible{23});

	resetCounters();
	queue = (queue);

	ASSERT_EQUAL(0, NonDefaultConstructible::nOfCopyConstructions);
}

void test_self_move_assignment_no_move_construction() {
	BoundedQueue<NonDefaultConstructible> queue{5};
	queue.push(NonDefaultConstructible{23});

	resetCounters();
	queue = std::move(queue);

	ASSERT_EQUAL(0, NonDefaultConstructible::nOfMoveConstructions);
}

void test_copy_assignment_deletes_previous_elements() {
	BoundedQueue<NonDefaultConstructible> queue{5}, other{5};
	queue.push(NonDefaultConstructible{23});

	resetCounters();
	queue = other;

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

void test_move_assignment_deletes_previous_elements_upon_destruction() {
	{
		BoundedQueue<NonDefaultConstructible> queue{5}, other{5};
		queue.push(NonDefaultConstructible{23});

		resetCounters();
		queue = std::move(other);
	}

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}



cute::suite make_suite_bounded_queue_non_default_constructible_element_type_suite(){
	cute::suite s;
	s.push_back(CUTE(test_new_queue_of_nondefaultconstructible_invokes_no_destructors));
	s.push_back(CUTE(test_element_in_queue_is_destroyed_once));
	s.push_back(CUTE(test_element_in_moved_queue_is_destroyed_once));
	s.push_back(CUTE(test_every_element_in_copied_queue_is_destroyed_once));
	s.push_back(CUTE(test_pop_destroys_element));
	s.push_back(CUTE(test_lvalue_push_copies_element));
	s.push_back(CUTE(test_rvalue_push_moves_element));
	s.push_back(CUTE(test_lvalue_push_must_not_copy_assign));
	s.push_back(CUTE(test_rvalue_push_must_not_move_assign));
	s.push_back(CUTE(test_self_move_assignment_unchanged_size));
	s.push_back(CUTE(test_self_copy_assignment_unchanged_size));
	s.push_back(CUTE(test_self_copy_assignment_no_copy_construction));
	s.push_back(CUTE(test_self_move_assignment_no_move_construction));
	s.push_back(CUTE(test_copy_assignment_deletes_previous_elements));
	s.push_back(CUTE(test_move_assignment_deletes_previous_elements_upon_destruction));
	return s;
}



