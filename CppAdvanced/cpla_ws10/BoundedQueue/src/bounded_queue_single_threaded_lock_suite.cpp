#include "bounded_queue_single_threaded_lock_suite.h"

#include "cute.h"
#include "BoundedQueue.h"
#include <type_traits>

#include <chrono>
using namespace std::chrono_literals;

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

template <typename TAG>
struct Counter{
	size_t count{};
	bool operator==(Counter const &other) const {
		return count == other.count;
	}
	Counter& operator++(){
		++count;
		return *this;
	}
	friend std::ostream& operator<<(std::ostream&out,Counter<TAG> const &c){
		return out << "Counter("<<c.count<<")";
	}
};
struct Wait:Counter<Wait> {
};
struct Notify:Counter<Notify> {
};
struct BadWaits:Counter<BadWaits>{
};

namespace single_threaded_condition_variable_counters {
static Wait wait_count { 0 };
static Notify notify_count { 0 };
static BadWaits bad_waits { 0 };
static bool docheck { false };
static void reset_counters() {
	using namespace single_threaded_condition_variable_counters;
	wait_count = Wait{0};
	notify_count = Notify{0};
	bad_waits = BadWaits{0};
	docheck = true;
}
}
struct single_threaded_condition_variable {
	single_threaded_condition_variable() {
		using namespace single_threaded_condition_variable_counters;
		docheck = false; // scharf stellen mit reset_counters()
	}

	~single_threaded_condition_variable() = default;
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
		return bad_waits == BadWaits{0} && wait_count.count <= notify_count.count;
	}
private:
	std::condition_variable_any inner_condition { };
};

void reset_counters() {
	single_threaded_test_mutex::reset_counters();
	single_threaded_condition_variable_counters::reset_counters();
}

void check_counters(Wait w, Notify n){
	using namespace single_threaded_condition_variable_counters;
	ASSERT_EQUALM("Waist",w.count,wait_count.count);
	ASSERT_EQUALM("Notifies",n.count,notify_count.count);
	ASSERT_EQUALM("BadWaits",BadWaits{0},bad_waits);
}


void test_push_rvalue_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.push(1);

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
	check_counters(Wait{1},Notify{1});
}

void test_push_rvalue_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.push(1);

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{1},Notify{1});
}

void test_push_lvalue_aquires_lock() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.push(i);

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
	check_counters(Wait{1},Notify{1});
}

void test_push_lvalue_releases_lock() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.push(i);

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{1},Notify{1});
}

void test_pop_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	queue.push(1);
	reset_counters();

	queue.pop();

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
	check_counters(Wait{1},Notify{1});
}

void test_pop_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	queue.push(1);
	reset_counters();

	queue.pop();

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{1},Notify{1});
}

void test_empty_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.empty();

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
	check_counters(Wait{0},Notify{0});
}

void test_empty_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.empty();

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{0},Notify{0});
}

void test_full_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.full();

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
	check_counters(Wait{0},Notify{0});
}

void test_full_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.full();

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{0},Notify{0});
}

void test_size_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.size();

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
	check_counters(Wait{0},Notify{0});
}

void test_size_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.size();

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{0},Notify{0});
}

void test_swap_aquires_both_locks() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 }, other { 4 };
	reset_counters();

	queue.swap(other);

	ASSERT_EQUAL(2, single_threaded_test_mutex::lock_count + single_threaded_test_mutex::try_lock_count);
	check_counters(Wait{0},Notify{2}); // swap notifies others
}

void test_swap_releases_two_locks() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 }, other { 4 };
	reset_counters();

	queue.swap(other);

	ASSERT_EQUAL(2, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{0},Notify{2}); // swap notfies others
}

void test_swap_aquires_tries_multiple_times_to_try_lock() {
	BoundedQueue<int, single_threaded_count_down_mutex<3>, single_threaded_condition_variable> queue { 5 }, other { 4 };
	reset_counters();

	queue.swap(other);

	ASSERT_EQUAL(4, single_threaded_test_mutex::try_lock_count);
	check_counters(Wait{0},Notify{2});
}

void test_swap_successful_after_delayed_lock() {
	BoundedQueue<int, single_threaded_count_down_mutex<1>, single_threaded_condition_variable> queue { 5 }, other { 4 };
	other.push(17);
	reset_counters();

	queue.swap(other);

	ASSERT_EQUAL(17, queue.pop());
	check_counters(Wait{1},Notify{4});
}

void test_try_push_rvalue_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.try_push(1);

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
	check_counters(Wait{0},Notify{1});
}

void test_try_push_rvalue_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.try_push(1);

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{0},Notify{1});
}

void test_try_push_lvalue_aquires_lock() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.try_push(i);

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
	check_counters(Wait{0},Notify{1});
}

void test_try_push_lvalue_releases_lock() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.try_push(i);

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
}

void test_try_pop_aquires_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	queue.push(1);
	reset_counters();

	queue.try_pop();

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
}

void test_try_pop_releases_lock() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	queue.push(1);
	reset_counters();

	queue.try_pop();

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{0},Notify{1});
}

void test_no_lock_on_size_constructor() {
	reset_counters();

	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };

	ASSERT_EQUAL(0, single_threaded_test_mutex::lock_count);
	check_counters(Wait{0},Notify{0});
}

void test_no_unlock_on_size_constructor() {
	reset_counters();

	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };

	ASSERT_EQUAL(0, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{0},Notify{0});
}

bool same_locks_and_unlocks() {
	return single_threaded_test_mutex::unlock_count == single_threaded_test_mutex::lock_count + single_threaded_test_mutex::try_lock_count;
}

void test_symmetric_lock_and_unlock_on_copy_constructor() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> copy { queue };

	ASSERT(same_locks_and_unlocks());
	check_counters(Wait{0},Notify{0});
}

void test_symmetric_lock_and_unlock_on_move_constructor() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> moved { std::move(queue) };

	ASSERT(same_locks_and_unlocks());
	check_counters(Wait{0},Notify{0});
}

void test_symmetric_lock_and_unlock_on_copy_assignment() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 }, copy { 4 };
	reset_counters();

	copy = queue;

	ASSERT(same_locks_and_unlocks());
	check_counters(Wait{0},Notify{1});
}

void test_symmetric_lock_and_unlock_on_move_assignment() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 }, moved { 4 };
	reset_counters();

	moved = std::move(queue);

	ASSERT(same_locks_and_unlocks());
	check_counters(Wait{0},Notify{1}); // move assignment notifies not_full!
}

void test_try_push_for_aquires_lock_on_empty_queue() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();
	queue.try_push_for(i, 1ms);

	ASSERT_EQUAL(1, single_threaded_test_mutex::lock_count);
	check_counters(Wait{1},Notify{1});
}

void test_try_push_for_releases_lock_on_empty_queue() {
	int i { 1 };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.try_push_for(i, 1ms);

	ASSERT_EQUAL(1, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{1},Notify{1});
}

void test_try_pop_for_aquires_lock_on_empty_queue() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.try_pop_for(1ms);
	ASSERT_EQUAL(2, single_threaded_test_mutex::lock_count);
	check_counters(Wait{1},Notify{0});
}

void test_try_pop_for_releases_lock_on_empty_queue() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 5 };
	reset_counters();

	queue.try_pop_for(1ms);
	ASSERT_EQUAL(2, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{1},Notify{0});
}

void test_try_push_for_aquires_lock_on_full_queue() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 1 };
	queue.push(1);
	reset_counters();

	queue.try_push_for(1, 1ms);

	ASSERT_EQUAL(2, single_threaded_test_mutex::lock_count);
	check_counters(Wait{1},Notify{0});
}

void test_try_push_for_releases_lock_on_full_queue() {
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 1 };
	queue.push(1);
	reset_counters();

	queue.try_push_for(1, 1ms);

	ASSERT_EQUAL(2, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{1},Notify{0});
}

void test_try_pop_for_aquires_lock_on_full_queue() {
	int result { };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 1 };
	queue.push(1);
	reset_counters();

	queue.try_push_for(result, 1ms);

	ASSERT_EQUAL(2, single_threaded_test_mutex::lock_count);
	check_counters(Wait{1},Notify{0});
}

void test_try_pop_for_releases_lock_on_full_queue() {
	int result { };
	BoundedQueue<int, single_threaded_test_mutex, single_threaded_condition_variable> queue { 1 };
	queue.push(1);
	reset_counters();

	queue.try_push_for(result, 1ms);

	ASSERT_EQUAL(2, single_threaded_test_mutex::unlock_count);
	check_counters(Wait{1},Notify{0});
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

