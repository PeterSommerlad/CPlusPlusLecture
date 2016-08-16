#include <thread>
#include <iostream>

int main() {
	using std::cout;
	using std::endl;

	std::thread t{[]{cout << "Hello Thread"<< endl;}};
	cout << "Hello Main" << endl;
}
