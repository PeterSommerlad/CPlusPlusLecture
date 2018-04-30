#include <future>
#include <iostream>
#include <thread>
#include <string>

#include <ios>

#include <ostream>

#include <utility>

std::string done_string(bool c){
	return c?"done":"not done";
}

thread_local bool done{}; // @suppress("Global Non Const Variable Problem")

std::string compute_the_answer(int i){
	using namespace std::literals;
	std::this_thread::sleep_for(1s);
	done=true;
	return "I am "s + done_string(done)+" the answer is "s + std::to_string(i);
}
int main(){
	using pt_fun = std::packaged_task<std::string(int)>;

	std::cout << "computing"<<std::endl;
	pt_fun task{compute_the_answer};
	auto future=task.get_future();
	std::thread compute{std::move(task),42};

	std::cout << future.get() << std::endl;
	std::cout << "main thread: " << done_string(done);
	compute.join();
}
