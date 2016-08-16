#include "bounded_queue_semantic_suite.h"

#include "cute.h"
#include "BoundedQueue.h"
#include "MemoryOperationCounter.h"



void test_queue_push_copies_element() {
	BoundedQueue<MemoryOperationCounter> queue { 1 };
	MemoryOperationCounter counter { }, expected { 1, 1, true };
	queue.push(counter);
	ASSERT_EQUAL(expected, queue.pop());
}

void test_queue_push_moves_element() {
	BoundedQueue<MemoryOperationCounter> queue { 1 };
	MemoryOperationCounter counter { }, expected { 2, 0, true };
	queue.push(std::move(counter));
	ASSERT_EQUAL(expected, queue.pop());
}

void test_element_in_queue_is_copied_along_copy_constructor() {
	BoundedQueue<MemoryOperationCounter> queue{ 1 };
	MemoryOperationCounter counter{}, expected{1, 2, true};
	queue.push(counter);
	BoundedQueue<MemoryOperationCounter> const & constQueue = queue;
	BoundedQueue<MemoryOperationCounter> queueCopied{constQueue};
	ASSERT_EQUAL(expected, queueCopied.pop());
}

void test_element_in_queue_is_copied_along_assignment_operator() {
	BoundedQueue<MemoryOperationCounter> queue{1}, queueCopied{1};
	MemoryOperationCounter counter{}, expected{1, 2, true};
	queue.push(counter);
	BoundedQueue<MemoryOperationCounter> const & constQueue = queue;
	queueCopied = constQueue;
	ASSERT_EQUAL(expected, queueCopied.pop());
}

void test_element_in_queue_is_moved_along_move_constructor() {
	BoundedQueue<MemoryOperationCounter> queue{1};
	MemoryOperationCounter counter{}, expected{2, 0, true};
	queue.push(std::move(counter));
	BoundedQueue<MemoryOperationCounter> queueMoved{std::move(queue)};
	ASSERT_EQUAL(expected, queueMoved.pop());
}

void test_element_in_queue_is_moved_along_assignment_operator() {
	BoundedQueue<MemoryOperationCounter> queue{1}, queueMoved{1};
	MemoryOperationCounter counter{}, expected{2, 0, true};
	queue.push(std::move(counter));
	queueMoved = std::move(queue);
	ASSERT_EQUAL(expected, queueMoved.pop());
}


void test_element_in_queue_is_copied_along_assignment_operator_multiple_copies() {
	BoundedQueue<MemoryOperationCounter> queue{1}, intermediate1{1}, intermediate2{1}, queueCopied{1};
	MemoryOperationCounter counter{}, expected{1, 4, true};
	queue.push(counter);
	queueCopied = intermediate2 = intermediate1 = queue;
	ASSERT_EQUAL(expected, queueCopied.pop());
}


void test_element_in_queue_is_moved_along_assignment_operator_multiple_moves() {
	BoundedQueue<MemoryOperationCounter> queue{1}, intermediate1{1}, intermediate2{1}, queueMoved{1};
	MemoryOperationCounter counter{}, expected{2, 0, true};
	queue.push(std::move(counter));
	queueMoved = std::move(intermediate1 = std::move(intermediate2 = std::move(queue)));
	ASSERT_EQUAL(expected, queueMoved.pop());
}


void test_element_queue_copy_is_returned_from_assignment() {
	BoundedQueue<MemoryOperationCounter> queue{1}, queueCopied{1};
	MemoryOperationCounter counter{}, expected{1, 2, true};
	queue.push(counter);
	BoundedQueue<MemoryOperationCounter> const & constQueue = queue;
	ASSERT_EQUAL(expected, (queueCopied = constQueue).pop());
}


void test_element_queue_moved_is_returned_from_assignment() {
	BoundedQueue<MemoryOperationCounter> queue{1}, queueMoved{1};
	MemoryOperationCounter counter{}, expected{2, 0, true};
	queue.push(std::move(counter));
	ASSERT_EQUAL(expected, (queueMoved = std::move(queue)).pop());
}

void test_capacity_is_copied_in_ctor() {
	//given
	BoundedQueue<MemoryOperationCounter> queue{4};
	queue.push(MemoryOperationCounter{});
	queue.push(MemoryOperationCounter{});

	//when
	BoundedQueue<MemoryOperationCounter> copy {queue};
	copy.push(MemoryOperationCounter{});
	copy.push(MemoryOperationCounter{});

	//then
	ASSERT(copy.full());
}

void test_capacity_is_copied_in_assignment() {
	//given
	BoundedQueue<MemoryOperationCounter> queue{4}, copy{1};
	queue.push(MemoryOperationCounter{});
	queue.push(MemoryOperationCounter{});

	//when
	copy = queue;
	copy.push(MemoryOperationCounter{});
	copy.push(MemoryOperationCounter{});

	//then
	ASSERT(copy.full());
}

void test_capacity_is_moved_in_ctor() {
	//given
	BoundedQueue<MemoryOperationCounter> queue{4};
	queue.push(MemoryOperationCounter{});
	queue.push(MemoryOperationCounter{});

	//when
	BoundedQueue<MemoryOperationCounter> copy {std::move(queue)};
	copy.push(MemoryOperationCounter{});
	copy.push(MemoryOperationCounter{});

	//then
	ASSERT(copy.full());
}

void test_capacity_is_moved_in_assignment() {
	//given
	BoundedQueue<MemoryOperationCounter> queue{4}, copy{1};
	queue.push(MemoryOperationCounter{});
	queue.push(MemoryOperationCounter{});

	//when
	copy = std::move(queue);
	copy.push(MemoryOperationCounter{});
	copy.push(MemoryOperationCounter{});

	//then
	ASSERT(copy.full());
}

cute::suite make_suite_bounded_queue_semantic_suite() {
	cute::suite s;
	s.push_back(CUTE(test_queue_push_moves_element));
	s.push_back(CUTE(test_queue_push_copies_element));
	s.push_back(CUTE(test_element_in_queue_is_copied_along_copy_constructor));
	s.push_back(CUTE(test_element_in_queue_is_copied_along_assignment_operator));
	s.push_back(CUTE(test_element_in_queue_is_moved_along_move_constructor));
	s.push_back(CUTE(test_element_in_queue_is_moved_along_assignment_operator));
	s.push_back(CUTE(test_element_in_queue_is_copied_along_assignment_operator_multiple_copies));
	s.push_back(CUTE(test_element_in_queue_is_moved_along_assignment_operator_multiple_moves));
	s.push_back(CUTE(test_element_queue_copy_is_returned_from_assignment));
	s.push_back(CUTE(test_element_queue_moved_is_returned_from_assignment));
	s.push_back(CUTE(test_capacity_is_copied_in_ctor));
	s.push_back(CUTE(test_capacity_is_copied_in_assignment));
	s.push_back(CUTE(test_capacity_is_moved_in_ctor));
	s.push_back(CUTE(test_capacity_is_moved_in_assignment));
	return s;
}

