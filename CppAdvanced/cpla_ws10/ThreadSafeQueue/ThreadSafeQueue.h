#ifndef THREADSAFEQUEUE_H_
#define THREADSAFEQUEUE_H_
// Adapted from Anthony Williams: C++ Concurrency in Action
#include <mutex>
#include <queue>

template <typename T, typename MUTEX=std::mutex>
struct threadsafe_queue {
//	using guard=std::lock_guard<MUTEX>;
//	using lock=std::unique_lock<MUTEX>;
	void push(T const &t){
		std::scoped_lock lk{mx};
		q.push(t);
		notEmpty.notify_one();
	}
	T pop(){
		std::unique_lock lk{mx};
		notEmpty.wait(lk,[this]{return !q.empty();});
		T t = q.front();
		q.pop();
		return t;
	}
	bool try_pop(T &t){
		std::scoped_lock lk{mx};
		if (q.empty()) return false;
		t = q.front();
		q.pop();
		return true;
	}
	bool empty() const{
		std::scoped_lock lk{mx};
		return q.empty();
	}
	void swap(threadsafe_queue& other){
		// can't be noexcept, because locks might throw
		if (this == &other)return;
		std::scoped_lock lock_both{mx,other.mx};
//		lock my_lock(mx,std::defer_lock);
//		lock other_lock(other.mx,std::defer_lock);
//		std::lock(my_lock,other_lock);
		std::swap(q,other.q);
		// no need to swap mutex or cv
	}
private:
	mutable MUTEX mx{};
	std::condition_variable notEmpty{};
	std::queue<T> q{};
};



#endif /* THREADSAFEQUEUE_H_ */
