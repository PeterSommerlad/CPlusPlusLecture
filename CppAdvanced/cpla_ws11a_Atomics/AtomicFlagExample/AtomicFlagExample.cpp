#include <atomic>
#include <thread>
#include <ostream>
#include <iostream>
using namespace std::this_thread;
void outputWhenReady(std::atomic_flag &flag
				    , std::ostream &out){
	while (flag.test_and_set(std::memory_order_acquire))
		yield();
	out<< "Here is thread: "<< get_id()<< std::endl;
	flag.clear(std::memory_order_release);
}
int main() {
    using namespace std::chrono_literals;
	std::atomic_flag flag{};
	std::cout<< "main() is thread: "<< get_id()<< std::endl;

	std::thread t{[&flag]{ // do not do &capture with non-atomics!
		sleep_for(1ms);
				outputWhenReady(flag,std::cout);
	}};
	sleep_for(1.001ms);
	outputWhenReady(flag, std::cout);
	t.join();
}
