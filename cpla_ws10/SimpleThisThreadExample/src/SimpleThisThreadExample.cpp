#include <thread>
#include <iostream>

int main() {
	using std::cout;
	using std::endl;
	using namespace std::this_thread;
	using namespace std::chrono_literals;

	std::thread t{[]{
			yield();sleep_for(10ms);
			cout << "Hello Thread "<<
					get_id()<< endl;
			}};
	cout << "Hello Main Thread " << get_id() << endl;
	sleep_for(1000ms);
	t.join();
}
