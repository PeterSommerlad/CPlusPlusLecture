#include "bounded_queue_heap_memory_suite.h"

#include "cute.h"
#include "BoundedQueue.h"
#include "times_literal.hpp"


struct AllocationTracker {
	static void* operator new(std::size_t sz) {
		AllocationTracker * ptr = static_cast<AllocationTracker*>(::operator new(sz));
		allocatedSingleObjects.push_back(ptr);
		return ptr;
	}

	static void* operator new[](std::size_t sz) {
		AllocationTracker * ptr = static_cast<AllocationTracker*>(::operator new[](sz));
		allocatedArrays.push_back(ptr);
		return ptr;
	}

	static void operator delete(void* ptr) {
		deallocatedSingleObjects.push_back(static_cast<AllocationTracker*>(ptr));
		::operator delete(ptr);
	}
	static void operator delete[](void* ptr) {
		deallocatedArrays.push_back(static_cast<AllocationTracker*>(ptr));
		::operator delete[](ptr);
	}

	static void* operator new  ( std::size_t count, void* ptr ) {
		return ::operator new(count, ptr);
	}

	static std::vector<AllocationTracker*> allocatedSingleObjects;
	static std::vector<AllocationTracker*> allocatedArrays;
	static std::vector<AllocationTracker*> deallocatedSingleObjects;
	static std::vector<AllocationTracker*> deallocatedArrays;
};

std::vector<AllocationTracker*> AllocationTracker::allocatedSingleObjects;
std::vector<AllocationTracker*> AllocationTracker::allocatedArrays;
std::vector<AllocationTracker*> AllocationTracker::deallocatedSingleObjects;
std::vector<AllocationTracker*> AllocationTracker::deallocatedArrays;


std::ostream & operator <<(std::ostream& out, AllocationTracker const * const ptr) {
	out << "0x" << std::hex << (unsigned long long)ptr << std::dec;
	return out;
}


void resetAllocationCounters() {
	AllocationTracker::allocatedSingleObjects.clear();
	AllocationTracker::allocatedArrays.clear();
	AllocationTracker::deallocatedSingleObjects.clear();
	AllocationTracker::deallocatedArrays.clear();
}

void test_allocation_of_default_bounded_queue() {
	resetAllocationCounters();
	{
		BoundedQueue<AllocationTracker> queue { 2 };
	}
	ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

void test_deallocation_of_default_bounded_queue() {
	resetAllocationCounters();
	{
		BoundedQueue<AllocationTracker> queue { 2 };
	}
	ASSERT_EQUAL(0, AllocationTracker::deallocatedArrays.size());
}

void test_no_undeleted_allocation_on_exception() {
	resetAllocationCounters();
	try {
		BoundedQueue<AllocationTracker> queue { 0 };
		FAILM("The tests expects the BoundedQueue not being constructible with size 0.");
	} catch(std::invalid_argument & e) {
		ASSERT_EQUAL(AllocationTracker::deallocatedArrays, AllocationTracker::allocatedArrays);
	}
}

void test_copy_constructor_allocates_a_new_queue() {
	resetAllocationCounters();
	BoundedQueue<AllocationTracker> queue { 15 };
	BoundedQueue<AllocationTracker> copy { queue };
	ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

void test_move_constructor_does_not_allocate_a_new_queue() {
	resetAllocationCounters();
	BoundedQueue<AllocationTracker> queue { 15 };
	BoundedQueue<AllocationTracker> moved { std::move(queue) };
	ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

void test_copy_assignment_one_additional_allocation() {
	resetAllocationCounters();
	BoundedQueue<AllocationTracker> queue { 3 }, copy { 2 };
	queue.push(AllocationTracker{});
	queue.push(AllocationTracker{});
	copy = queue;
	ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

void test_move_assignment_no_additional_allocation() {
	resetAllocationCounters();
	BoundedQueue<AllocationTracker> queue { 3 }, move { 2 };
	queue.push(AllocationTracker{});
	queue.push(AllocationTracker{});
	move = std::move(queue);
	ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

void test_copy_self_assignment_no_additional_allocation() {
	resetAllocationCounters();
	BoundedQueue<AllocationTracker> queue { 3 };
	queue.push(AllocationTracker{});
	queue.push(AllocationTracker{});
	queue = (queue);
	ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}

void test_move_self_assignment_no_addtional_allocation() {
	resetAllocationCounters();
	BoundedQueue<AllocationTracker> queue { 3 };
	queue.push(AllocationTracker{});
	queue.push(AllocationTracker{});
	queue = std::move(queue);
	ASSERT_EQUAL(0, AllocationTracker::allocatedArrays.size());
}



struct CopyCounter {
	CopyCounter() = default;
	CopyCounter(CopyCounter const & other) {
		copy_counter++;
	}
	CopyCounter& operator=(CopyCounter const & other) {
		copy_counter++;
		return *this;
	}
	CopyCounter(CopyCounter &&) = default;
	CopyCounter& operator=(CopyCounter &&) = default;

	static unsigned copy_counter;
	static void resetCopyCounter() {
		copy_counter = 0;
	}
};

unsigned CopyCounter::copy_counter {0};

using namespace times::literal;

void test_copy_only_initialized_elements_in_copy_construction(){
	CopyCounter::resetCopyCounter();
	BoundedQueue<CopyCounter> queue{100};
	100_times([&](){
		queue.push(CopyCounter{});
	});
	75_times([&](){
		queue.pop();
	});
	25_times([&](){
		queue.push(CopyCounter{});
	});
	BoundedQueue<CopyCounter> copy{queue};
	ASSERT_EQUAL(50, CopyCounter::copy_counter);
}

void test_copy_only_initialized_elements_in_copy_assignment(){
	CopyCounter::resetCopyCounter();
	BoundedQueue<CopyCounter> queue{100}, copy{1};
	100_times([&](){
		queue.push(CopyCounter{});
	});
	75_times([&](){
		queue.pop();
	});
	25_times([&](){
		queue.push(CopyCounter{});
	});
	copy = queue;
	ASSERT_EQUAL(50, CopyCounter::copy_counter);
}


cute::suite make_suite_bounded_queue_heap_memory_suite() {
	cute::suite s;
	s.push_back(CUTE(test_allocation_of_default_bounded_queue));
	s.push_back(CUTE(test_deallocation_of_default_bounded_queue));
	s.push_back(CUTE(test_no_undeleted_allocation_on_exception));
	s.push_back(CUTE(test_copy_constructor_allocates_a_new_queue));
	s.push_back(CUTE(test_copy_self_assignment_no_additional_allocation));
	s.push_back(CUTE(test_move_self_assignment_no_addtional_allocation));
	s.push_back(CUTE(test_copy_only_initialized_elements_in_copy_construction));
	s.push_back(CUTE(test_copy_only_initialized_elements_in_copy_assignment));
	s.push_back(CUTE(test_move_constructor_does_not_allocate_a_new_queue));
	s.push_back(CUTE(test_copy_assignment_one_additional_allocation));
	s.push_back(CUTE(test_move_assignment_no_additional_allocation));
	return s;
}

