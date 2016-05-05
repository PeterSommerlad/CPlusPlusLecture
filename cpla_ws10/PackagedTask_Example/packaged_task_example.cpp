#include <future>
#include <iostream>
#include <thread>
#include <string>

thread_local bool done{};

std::string compute_the_answer(int i){
	using namespace std::literals;
	std::this_thread::sleep_for(1s);
	done=true;
	return "I am "s + std::to_string(done)+" the answer is "s + std::to_string(i);
}
int main(){
	using pt_fun = std::packaged_task<std::string(int)>;

	std::cout << "computing"<<std::endl;
	pt_fun task{compute_the_answer};
	auto future=task.get_future();
	std::thread compute{std::ref(task),42};

	std::cout << future.get() << std::endl;
	std::cout << std::boolalpha << done;
	compute.join();
}
