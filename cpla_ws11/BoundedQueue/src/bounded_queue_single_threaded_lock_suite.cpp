#include "bounded_queue_single_threaded_lock_suite.h"

#include "cute.h"
#include "BoundedQueue.h"
#include <type_traits>

struct single_threaded_test_mutex {
	static unsigned lock_count;
	static unsigned unlock_count;
	static unsigned try_lock_count;

	void lock() {
		lock_count++;
	}

	void unlock() {
		unlock_count++;
	}

	bool try_lock() {
		try_lock_count++;
		return true;
	}

	static void reset_counters() {
		lock_count = 0;
		unlock_count = 0;
		try_lock_count = 0;
	}
};

unsigned single_threaded_test_mutex::lock_count { 0 };
unsigned single_threaded_test_mutex::unlock_count { 0 };
unsigned single_threaded_test_mutex::try_lock_count { 0 };

template<std::size_t nOfFalseTries>
struct single_threaded_count_down_mutex: public single_threaded_test_mutex {
	std::size_t remaining_tries = nOfFalseTries;

	bool try_lock() {
		single_threaded_test_mutex::try_lock();
		if (remaining_tries == 0) {
			return true;
		}
		remaining_tries--;
		return false;
	}
};
namespace single_threaded_condition_variable_counters {
static size_t wait_count { 0 };
static size_t notify_count { 0 };
static size_t bad_waits { 0 };
static bool docheck { false };
static void reset_counters() {
	using namespace single_threaded_condition_variable_counters;
	wait_count = 0;
	notify_count = 0;
	bad_waits = 0;
	docheck = true;
}
}
template<size_t waitc = 0, size_t notifyc = 0, bool DO_CHECK = false>
struct single_threaded_condition_variable {
	single_threaded_condition_variable() {
		using namespace single_threaded_condition_variable_counters;
		docheck = DO_CHECK; // scharf stellen mit reset_counters()
	}
	~single_threaded_condition_variable() noexcept(false) {
		using namespace single_threaded_condition_variable_counters;
		if (!docheck)
			return;
		try {
			ASSERT_EQUAL(waitc, wait_count);
			ASSERT_EQUAL(notifyc, notify_count);
			ASSERT_EQUAL(0, bad_waits);
		} catch (...) {
			docheck = false;
			throw;
		}
	}
	template<typename LOCK, typename COND>
	void wait(LOCK & mx, COND cond) {
		using namespace single_threaded_condition_variable_counters;
		static_assert(std::is_convertible<decltype(cond()),bool>::value,"condition must return bool");
		++wait_count;
		inner_condition.wait(mx, cond);
		ASSERT(cond());
	}
	template<typename LOCK>
	void wait(LOCK & mx) {
		using namespace single_threaded_condition_variable_counters;
//		static_assert(false,"must not use wait without condition, bad practice");
		++wait_count;
		inner_condition.wait(mx);
	}
	template<typename LOCK, typename COND, typename REP, typename PER>
	bool wait_for(LOCK & mx, std::chrono::duration<REP, PER> const & dur, COND cond) {
		using namespace single_threaded_condition_variable_counters;
		static_assert(std::is_convertible<decltype(cond()),bool>::value,"condition must return bool");
		++wait_count;
		return inner_condition.wait_for(mx, dur, cond);
	}
	template<typename LOCK, typename REP, typename PER>
	bool wait_for(LOCK & mx, std::chrono::duration<REP, PER> const & dur) {
		using namespace single_threaded_condition_variable_counters;
//		static_assert(false,"must not use wait without condition, bad practice");
		++wait_count;
		return inner_condition.wait_for(mx, dur);
	}
	void notify_all() {
		using namespace single_threaded_condition_variable_counters;
		++notify_count;
		inner_condition.notify_all();
	}
	void notify_one() {
		using namespace single_threaded_condition_variable_counters;
		++notify_count;
		inner_condition.notify_one();
	}
	static bool check() {
		using namespace single_threaded_condition_variable_counters;
		return bad_waits == 0 && wait_count <= notify_count;
	}
private:
	std::condition_variable_any inner_condition { };
};

void reset_counters() {
	single_threaded_test_mutex::reset_counters();
	single_threaded_condition_variable_counters::reset_counters();
}

void test_push_rvalue_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue { 5 };
	reset_counters();

	queue.push(1);

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
}

void test_push_rvalue_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue { 5 };
	reset_counters();

	queue.push(1);

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
}

void test_push_lvalue_aquires_lock() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue { 5 };
	reset_counters();

	queue.push(i);

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
}

void test_push_lvalue_releases_lock() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue { 5 };
	reset_counters();

	queue.push(i);

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
}

void test_pop_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue { 5 };
	queue.push(1);
	reset_counters();

	queue.pop();

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
}

void test_pop_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue { 5 };
	queue.push(1);
	reset_counters();

	queue.pop();

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
}

void test_empty_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue { 5 };
	reset_counters();

	queue.empty();

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
}

void test_empty_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue { 5 };
	reset_counters();

	queue.empty();

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
}

void test_full_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue { 5 };
	reset_counters();

	queue.full();

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
}

void test_full_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue { 5 };
	reset_counters();

	queue.full();

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
}

void test_size_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue { 5 };
	reset_counters();

	queue.size();

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
}

void test_size_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<>> queue { 5 };
	reset_counters();

	queue.size();

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
}

void test_swap_aquires_both_locks() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<>> queue { 5 }, other { 4 };
	reset_counters();

	queue.swap(other);

	ASSERT_EQUAL(2, single_threaded_test_mutex::lock_count + single_threaded_test_mutex::try_lock_count);
}

void test_swap_releases_two_locks() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<>> queue { 5 }, other { 4 };
	reset_counters();

	queue.swap(other);

	ASSERT_EQUAL(2, single_threaded_test_mutex::unlock_count);
}

void test_swap_aquires_tries_multiple_times_to_try_lock() {
	BoundedQueue<int, single_threaded_count_down_mutex<3>, single_threaded_condition_variable<>> queue { 5 }, other { 4 };
	reset_counters();

	queue.swap(other);

	ASSERT_EQUAL(4, single_threaded_test_mutex::try_lock_count);
}

void test_swap_successful_after_delayed_lock() {
	BoundedQueue<int, single_threaded_count_down_mutex<1>, single_threaded_condition_variable<1, 1>> queue { 5 }, other { 4 };
	other.push(17);
	reset_counters();

	queue.swap(other);

	ASSERT_EQUAL(17, queue.pop());
}

void test_try_push_rvalue_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue { 5 };
	reset_counters();

	queue.try_push(1);

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
}

void test_try_push_rvalue_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue { 5 };
	reset_counters();

	queue.try_push(1);

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
}

void test_try_push_lvalue_aquires_lock() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue { 5 };
	reset_counters();

	queue.try_push(i);

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
}

void test_try_push_lvalue_releases_lock() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue { 5 };
	reset_counters();

	queue.try_push(i);

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
}

void test_try_pop_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue { 5 };
	queue.push(1);
	int result { };
	reset_counters();

	queue.try_pop(result);

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
}

void test_try_pop_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue { 5 };
	queue.push(1);
	int result { };
	reset_counters();

	queue.try_pop(result);

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
}

void test_no_lock_on_size_constructor() {
	reset_counters();

	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> queue { 5 };

	ASSERT_EQUAL(0, single_threaded_test_mutex::lock_count);
}

void test_no_unlock_on_size_constructor() {
	reset_counters();

	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> queue { 5 };

	ASSERT_EQUAL(0, single_threaded_test_mutex::unlock_count);
}

bool same_locks_and_unlocks() {
	return single_threaded_test_mutex::unlock_count == single_threaded_test_mutex::lock_count + single_threaded_test_mutex::try_lock_count;
}

void test_symmetric_lock_and_unlock_on_copy_constructor() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> queue { 5 };
	reset_counters();

	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> copy { queue };

	ASSERT(same_locks_and_unlocks());
}

void test_symmetric_lock_and_unlock_on_move_constructor() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> queue { 5 };
	reset_counters();

	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0, true>> moved { std::move(queue) };

	ASSERT(same_locks_and_unlocks());
}

void test_symmetric_lock_and_unlock_on_copy_assignment() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 1>> queue { 5 }, copy { 4 };
	reset_counters();

	copy = queue;

	ASSERT(same_locks_and_unlocks());
}

void test_symmetric_lock_and_unlock_on_move_assignment() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<0, 0>> queue { 5 }, moved { 4 };
	reset_counters();

	moved = std::move(queue);

	ASSERT(same_locks_and_unlocks());
}

void test_try_push_for_aquires_lock_on_empty_queue() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue { 5 };
	reset_counters();

	queue.try_push_for(i, std::chrono::milliseconds { 1 });

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
}

void test_try_push_for_releases_lock_on_empty_queue() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 1>> queue { 5 };
	reset_counters();

	queue.try_push_for(i, std::chrono::milliseconds { 1 });

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
}

void test_try_pop_for_aquires_lock_on_empty_queue() {
	int result { };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue { 5 };
	reset_counters();

	queue.try_pop_for(result, std::chrono::milliseconds { 1 });

	ASSERT_EQUAL(2, single_threaded_test_mutex::lock_count);
}

void test_try_pop_for_releases_lock_on_empty_queue() {
	int result { };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue { 5 };
	reset_counters();

	queue.try_pop_for(result, std::chrono::milliseconds { 1 });

	ASSERT_EQUAL(2, single_threaded_test_mutex::unlock_count);
}

void test_try_push_for_aquires_lock_on_full_queue() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue { 1 };
	queue.push(1);
	reset_counters();

	queue.try_push_for(1, std::chrono::milliseconds { 1 });

	ASSERT_EQUAL(2, single_threaded_test_mutex::lock_count);
}

void test_try_push_for_releases_lock_on_full_queue() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue { 1 };
	queue.push(1);
	reset_counters();

	queue.try_push_for(1, std::chrono::milliseconds { 1 });

	ASSERT_EQUAL(2, single_threaded_test_mutex::unlock_count);
}

void test_try_pop_for_aquires_lock_on_full_queue() {
	int result { };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue { 1 };
	queue.push(1);
	reset_counters();

	queue.try_push_for(result, std::chrono::milliseconds { 1 });

	ASSERT_EQUAL(2, single_threaded_test_mutex::lock_count);
}

void test_try_pop_for_releases_lock_on_full_queue() {
	int result { };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable<1, 0>> queue { 1 };
	queue.push(1);
	reset_counters();

	queue.try_push_for(result, std::chrono::milliseconds { 1 });

	ASSERT_EQUAL(2, single_threaded_test_mutex::unlock_count);
}

cute::suite make_suite_bounded_queue_single_threaded_lock_suite() {
	cute::suite s;
	s.push_back(CUTE(test_push_rvalue_aquires_lock));
	s.push_back(CUTE(test_push_rvalue_releases_lock));
	s.push_back(CUTE(test_push_lvalue_aquires_lock));
	s.push_back(CUTE(test_push_lvalue_releases_lock));
	s.push_back(CUTE(test_pop_aquires_lock));
	s.push_back(CUTE(test_pop_releases_lock));
	s.push_back(CUTE(test_empty_aquires_lock));
	s.push_back(CUTE(test_empty_releases_lock));
	s.push_back(CUTE(test_full_aquires_lock));
	s.push_back(CUTE(test_full_releases_lock));
	s.push_back(CUTE(test_size_aquires_lock));
	s.push_back(CUTE(test_size_releases_lock));
	s.push_back(CUTE(test_swap_aquires_both_locks));
	s.push_back(CUTE(test_swap_releases_two_locks));
	s.push_back(CUTE(test_try_push_rvalue_aquires_lock));
	s.push_back(CUTE(test_try_push_rvalue_releases_lock));
	s.push_back(CUTE(test_try_push_lvalue_aquires_lock));
	s.push_back(CUTE(test_try_push_lvalue_releases_lock));
	s.push_back(CUTE(test_try_pop_aquires_lock));
	s.push_back(CUTE(test_try_pop_releases_lock));
	s.push_back(CUTE(test_swap_aquires_tries_multiple_times_to_try_lock));
	s.push_back(CUTE(test_swap_successful_after_delayed_lock));
	s.push_back(CUTE(test_no_lock_on_size_constructor));
	s.push_back(CUTE(test_no_unlock_on_size_constructor));
	s.push_back(CUTE(test_symmetric_lock_and_unlock_on_copy_constructor));
	s.push_back(CUTE(test_symmetric_lock_and_unlock_on_move_constructor));
	s.push_back(CUTE(test_symmetric_lock_and_unlock_on_copy_assignment));
	s.push_back(CUTE(test_symmetric_lock_and_unlock_on_move_assignment));
	s.push_back(CUTE(test_try_push_for_aquires_lock_on_empty_queue));
	s.push_back(CUTE(test_try_push_for_releases_lock_on_empty_queue));
	s.push_back(CUTE(test_try_pop_for_aquires_lock_on_empty_queue));
	s.push_back(CUTE(test_try_pop_for_releases_lock_on_empty_queue));
	s.push_back(CUTE(test_try_push_for_aquires_lock_on_full_queue));
	s.push_back(CUTE(test_try_push_for_releases_lock_on_full_queue));
	s.push_back(CUTE(test_try_pop_for_aquires_lock_on_full_queue));
	s.push_back(CUTE(test_try_pop_for_releases_lock_on_full_queue));
	return s;
}

