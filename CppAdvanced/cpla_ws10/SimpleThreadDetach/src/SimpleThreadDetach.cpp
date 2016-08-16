#include <thread>
#include <chrono>
#include <iostream>
#include <unistd.h>

int main() {
	using namespace std::chrono_literals;
	using std::cout;
	using std::endl;
	using namespace std::this_thread;

	std::thread{[]{
			sleep_for(30us);
			write(1, "Hello Thread\n",13);}
			// should not use cout, it might have gone when called
	}.detach();
	cout << "Hello Main" << endl;
}
