#include <string>
#include <thread>
#include <chrono>
#include <iostream>
// what can go wrong with this code?
void startThread() {
	using namespace std::chrono_literals;
	std::string local{"local"};
	std::thread t{[&] {
		std::this_thread::sleep_for(1s);
		std::cout << "local: " << local << std::endl;
	}};
	t.detach();
}

int main(int argc, char **argv) {
	using namespace std::chrono_literals;
	startThread();
	std::this_thread::sleep_for(2s);
}
