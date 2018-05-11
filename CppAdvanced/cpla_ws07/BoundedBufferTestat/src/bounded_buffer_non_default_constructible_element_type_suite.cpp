#include "bounded_buffer_non_default_constructible_element_type_suite.h"
#include "cute.h"
#include "BoundedBuffer.h"
#include <stdexcept>

struct NonDefaultConstructible {
	NonDefaultConstructible(int) : value{1234} {}

	~NonDefaultConstructible() {
		throwIfNotInitialized();
		nOfDtorCalls++;
	}

	NonDefaultConstructible(NonDefaultConstructible const & other) : value{other.value} {
		throwIfNotInitialized();
		nOfCopyConstructions++;
	}

	NonDefaultConstructible& operator=(NonDefaultConstructible const & other) {
		throwIfNotInitialized();
		other.throwIfNotInitialized();
		value = other.value;
		nOfCopyAssignments++;
		return *this;
	}

	NonDefaultConstructible& operator=(NonDefaultConstructible && other) {
		throwIfNotInitialized();
		other.throwIfNotInitialized();
		std::swap(value, other.value);
		nOfMoveAssignments++;
		return *this;
	}

	NonDefaultConstructible(NonDefaultConstructible && other) : value{1234} {
		other.throwIfNotInitialized();
		std::swap(value, other.value);
		nOfMoveConstructions++;
	}

	static unsigned nOfCopyConstructions;
	static unsigned nOfCopyAssignments;
	static unsigned nOfMoveConstructions;
	static unsigned nOfMoveAssignments;
	static unsigned nOfDtorCalls;
private:
	void throwIfNotInitialized() const {
		if (value != 1234) {
			throw std::logic_error{"Operation on NDC with value: " + value};
		}
	}
	volatile unsigned value;
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

void test_new_buffer_of_nondefaultconstructible_invokes_no_destructors() {
	resetCounters();
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	ASSERT_EQUAL(0, NonDefaultConstructible::nOfDtorCalls);
}

void test_element_in_buffer_is_destroyed_once() {
	{
		BoundedBuffer<NonDefaultConstructible> buffer{5};
		buffer.push(NonDefaultConstructible{23});
		resetCounters();
	}
	ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

void test_element_in_moved_buffer_is_destroyed_once() {
	{
		BoundedBuffer<NonDefaultConstructible> buffer{5};
		buffer.push(NonDefaultConstructible{23});
		resetCounters();

		BoundedBuffer<NonDefaultConstructible> moved{std::move(buffer)};
	}

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

void test_every_element_in_copied_buffer_is_destroyed_once() {
	{
		BoundedBuffer<NonDefaultConstructible> buffer{5};
		buffer.push(NonDefaultConstructible{23});
		resetCounters();

		BoundedBuffer<NonDefaultConstructible> copy{buffer};
	}
	ASSERT_EQUAL(2, NonDefaultConstructible::nOfDtorCalls);
}

void test_pop_destroys_element() {
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	buffer.push(NonDefaultConstructible{23});
	resetCounters();

	buffer.pop();

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

void test_lvalue_push_copies_element() {
	resetCounters();
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	NonDefaultConstructible element{23};

	buffer.push(element);

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfCopyConstructions);
}

void test_rvalue_push_moves_element() {
	resetCounters();
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	NonDefaultConstructible element{23};

	buffer.push(std::move(element));

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfMoveConstructions);
}

void test_lvalue_push_must_not_copy_assign() {
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	NonDefaultConstructible element{23};

	resetCounters();
	buffer.push(element);

	ASSERT_EQUAL(0, NonDefaultConstructible::nOfCopyAssignments);
}

void test_rvalue_push_must_not_move_assign() {
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	NonDefaultConstructible element{23};

	resetCounters();
	buffer.push(std::move(element));

	ASSERT_EQUAL(0, NonDefaultConstructible::nOfMoveAssignments);
}

cute::suite make_suite_bounded_buffer_non_default_constructible_element_type_suite(){
	cute::suite s;
	s.push_back(CUTE(test_new_buffer_of_nondefaultconstructible_invokes_no_destructors));
	s.push_back(CUTE(test_element_in_buffer_is_destroyed_once));
	s.push_back(CUTE(test_element_in_moved_buffer_is_destroyed_once));
	s.push_back(CUTE(test_every_element_in_copied_buffer_is_destroyed_once));
	s.push_back(CUTE(test_pop_destroys_element));
	s.push_back(CUTE(test_lvalue_push_copies_element));
	s.push_back(CUTE(test_rvalue_push_moves_element));
	s.push_back(CUTE(test_lvalue_push_must_not_copy_assign));
	s.push_back(CUTE(test_rvalue_push_must_not_move_assign));
	return s;
}



