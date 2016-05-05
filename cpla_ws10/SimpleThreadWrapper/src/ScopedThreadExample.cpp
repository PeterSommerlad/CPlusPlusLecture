#include <thread>
#include <iostream>

// adapted from Athony Williams: C++ Concurrency in Action
struct scoped_thread{
	scoped_thread(std::thread t)
	:the_thread{std::move(t)}{
		if (! the_thread.joinable())
			throw std::logic_error{"no thread"};
	}
	~scoped_thread(){ the_thread.join(); }
private:
	// copying (and moving) is implicitly deleted
	// because std::thread is only movable
	std::thread the_thread;
};


int main() {
	using std::cout;
	using std::endl;

	scoped_thread t{std::thread{
		[]{cout << "Hello Thread"<< endl;}}};
	cout << "Hello Main" << endl;
}
