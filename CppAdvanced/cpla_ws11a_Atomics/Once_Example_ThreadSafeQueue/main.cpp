#include "ThreadSafeQueue.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <cassert>

#include <functional>

void initfun(threadsafe_queue<int>&q){
	q.push(999);
}
int main(){
	using namespace std::this_thread;
	using namespace std::chrono_literals;
	threadsafe_queue<int> queue { };
	std::once_flag init{};

	std::thread prod1{[&]{
		sleep_for(10ms);
		call_once(init,initfun,std::ref(queue));
		for(int i=0; i < 10; ++i){
			queue.push(i);
			yield();//sleep_for(1ms);
		}
	}};
	std::thread prod2{[&]{
		sleep_for(9ms);
		call_once(init,initfun,std::ref(queue));
		for(int i=0; i < 10; ++i){
			queue.push(i+10);
			yield();//sleep_for(1ms);
		}
	}};
	std::thread cons{[&]{
		do {
			std::cout << queue.pop() << '\n';
			yield();
		} while (!queue.empty());
	}};
	prod1.join(), prod2.join(),cons.join();
	threadsafe_queue<int> q2 { };
	q2.push(1);
	queue.swap(q2);
	assert(1==queue.pop());
	assert(queue.empty());
}



