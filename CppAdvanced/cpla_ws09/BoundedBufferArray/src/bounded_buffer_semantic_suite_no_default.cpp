#include "bounded_buffer_semantic_suite_no_default.h"
#include "cute.h"
#include "BoundedBuffer.h"
#include <utility>
namespace no_default_ctor {
struct MemoryOperationCounter {

	MemoryOperationCounter(unsigned moves, unsigned copies=0, bool known_state=true) :
			moves { moves }, copies { copies }, known_state { known_state } {
	}

	MemoryOperationCounter(MemoryOperationCounter && source) :
			moves { std::move(source.moves) }, copies { std::move(source.copies) }, known_state { std::move(source.known_state) } {
		moves++;
		source.known_state = false;
	}

	MemoryOperationCounter & operator=(MemoryOperationCounter && source) & noexcept {
		copyFrom(source);
		moves++;
		source.known_state = false;
		return *this;
	}

	MemoryOperationCounter(MemoryOperationCounter const & source) :
			moves { std::move(source.moves) }, copies { std::move(source.copies) }, known_state { std::move(source.known_state) } {
		copies++;
	}

	MemoryOperationCounter & operator=(MemoryOperationCounter const & source) & noexcept {
		copyFrom(source);
		copies++;
		return *this;
	}

	bool operator==(MemoryOperationCounter const & other) const {
		return (moves == other.moves) && (copies == other.copies) == (known_state == other.known_state);
	}

	void print(std::ostream & os) const {
		os << "MemoryOperationsCounter{moves: " << moves << ", copies: " << copies << ", known_state: " << known_state << "}\n";
	}

public:
	unsigned moves { 0 };
	unsigned copies { 0 };
	bool known_state { true };

	void copyFrom(MemoryOperationCounter const & source) {
		moves = source.moves;
		copies = source.copies;
		known_state = source.known_state;
	}
};

std::ostream & operator <<(std::ostream & os, MemoryOperationCounter const & counter) {
	counter.print(os);
	return os;
}


void test_buffer_push_copies_element() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer { };
	MemoryOperationCounter counter { 0 }, expected { 0, 1, true };
	buffer.push(counter);
	ASSERT_EQUAL(expected, buffer.front());
}

void test_buffer_push_moves_element() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer { };
	MemoryOperationCounter counter { 0 }, expected { 1, 0, true };
	buffer.push(std::move(counter));
	ASSERT_EQUAL(expected, buffer.front());
}

void test_moved_over_and_from_elements_are_destructed() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{};
	MemoryOperationCounter counter{ 0 }, expected{0, 2, true};
	buffer.push(counter);
	BoundedBuffer<MemoryOperationCounter, 1> const & constBuffer = buffer;
	BoundedBuffer<MemoryOperationCounter, 1> bufferCopied{constBuffer};
	ASSERT_EQUAL(expected, bufferCopied.front());
}

void test_element_in_buffer_is_copied_along_assignment_operator() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferCopied{};
	MemoryOperationCounter counter{0 }, expected{0, 2, true};
	buffer.push(counter);
	BoundedBuffer<MemoryOperationCounter, 1> const & constBuffer = buffer;
	bufferCopied = constBuffer;
	ASSERT_EQUAL(expected.copies, bufferCopied.front().copies);
}

void test_element_in_buffer_is_moved_along_move_constructor() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{};
	MemoryOperationCounter counter{0 }, expected{2, 0, true};
	buffer.push(std::move(counter));
	BoundedBuffer<MemoryOperationCounter, 1> bufferCopied{std::move(buffer)};
	ASSERT_EQUAL(expected, bufferCopied.front());
}

void test_element_in_buffer_is_moved_along_assignment_operator() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferMoved{};
	MemoryOperationCounter counter{0 }, expected{2, 0, true};
	buffer.push(std::move(counter));
	bufferMoved = std::move(buffer);
	ASSERT_EQUAL(expected, bufferMoved.front());
}


void test_element_in_buffer_is_copied_along_assignment_operator_multiple_copies() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, intermediate1{}, intermediate2{}, bufferCopied{};
	MemoryOperationCounter counter{0}, expected{0, 4, true};
	buffer.push(counter);
	bufferCopied = intermediate2 = intermediate1 = buffer;
	ASSERT_EQUAL(expected.copies, bufferCopied.front().copies);
}


void test_element_in_buffer_is_moved_along_assignment_operator_multiple_moves() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, intermediate1{}, intermediate2{}, bufferMoved{};
	MemoryOperationCounter counter{0}, expected{4, 0, true};
	buffer.push(std::move(counter));
	bufferMoved = std::move(intermediate1 = std::move(intermediate2 = std::move(buffer)));
	ASSERT_EQUAL(expected, bufferMoved.front());
}


void test_element_buffer_copy_is_returned_from_assignment() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferCopied{};
	MemoryOperationCounter counter{0}, expected{0, 2, true};
	buffer.push(counter);
	BoundedBuffer<MemoryOperationCounter, 1> const & constBuffer = buffer;
	ASSERT_EQUAL(expected.copies, (bufferCopied = constBuffer).front().copies);
}


void test_element_buffer_moved_is_returned_from_assignment() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferMoved{};
	MemoryOperationCounter counter{0}, expected{2, 0, true};
	buffer.push(std::move(counter));
	ASSERT_EQUAL(expected, (bufferMoved = std::move(buffer)).front());
}
}
cute::suite make_suite_bounded_buffer_semantic_suite_no_default() {
	cute::suite s;
	s.push_back(CUTE(no_default_ctor::test_element_buffer_moved_is_returned_from_assignment));
	s.push_back(CUTE(no_default_ctor::test_element_buffer_copy_is_returned_from_assignment));
	s.push_back(CUTE(no_default_ctor::test_element_in_buffer_is_moved_along_assignment_operator_multiple_moves));
	s.push_back(CUTE(no_default_ctor::test_element_in_buffer_is_copied_along_assignment_operator_multiple_copies));
	s.push_back(CUTE(no_default_ctor::test_element_in_buffer_is_moved_along_assignment_operator));
	s.push_back(CUTE(no_default_ctor::test_element_in_buffer_is_moved_along_move_constructor));
	s.push_back(CUTE(no_default_ctor::test_element_in_buffer_is_copied_along_assignment_operator));
	s.push_back(CUTE(no_default_ctor::test_moved_over_and_from_elements_are_destructed));
	s.push_back(CUTE(no_default_ctor::test_buffer_push_moves_element));
	s.push_back(CUTE(no_default_ctor::test_buffer_push_copies_element));
	return s;
}

