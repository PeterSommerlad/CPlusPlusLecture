#include <iostream>
#include <future>
#include <thread>

std::ostream &operator<<(std::ostream &out,std::future_status stat){
	switch(stat){
	case std::future_status::ready: return out << "ready";
	case std::future_status::deferred:return  out << "deferred";
	case std::future_status::timeout: return out << "timeout";
	}
	return out;
}

void compute(std::promise<int>&&promise){
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(1s);
	promise.set_value(42);
	//promise.set_value_at_thread_exit(42);
	std::this_thread::sleep_for(1s);
}

int main(){
	using namespace std::chrono_literals;
	std::promise<int> promise{};
	auto future=promise.get_future(); // only once allowed

	std::thread t{compute,std::move(promise)};
	std::cout << std::boolalpha;
	std::cout << "future.wait_for? "<< future.wait_for(1s)<< std::endl;
	std::cout << "future.wait_for? "<< future.wait_for(3s)<< std::endl;
	std::cout << "the answer is "<< future.get() << std::endl;
	t.join();
}





