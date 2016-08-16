#include <atomic>
#include <thread>
#include <iostream>
using namespace std::this_thread;
using namespace std::chrono_literals;
void outputWhenReady(std::atomic_flag &flag
				    , std::ostream &out){
	while (flag.test_and_set(std::memory_order_acquire))
		yield();
	out<< "Here is thread: "<< get_id()<< std::endl;
	flag.clear(std::memory_order_release);
}
int main() {
	using std::cout;
	using std::endl;
	std::atomic_flag flag{};

	std::thread t{[&flag]{
		sleep_for(1ms);
		outputWhenReady(flag,cout);
	}};
	sleep_for(1ms);
	outputWhenReady(flag,std::cout);
	t.join();
}
