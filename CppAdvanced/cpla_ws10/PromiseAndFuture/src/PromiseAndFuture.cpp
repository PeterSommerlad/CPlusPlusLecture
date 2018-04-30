#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>
#include <ostream>

void compute(int num, int den, std::promise<int> p) {
	if (den == 0) {
		std::logic_error e{"must not divide by 0"};
		auto const e_ptr = std::make_exception_ptr(e);
		p.set_exception(e_ptr);
	} else {
		auto const result = num / den;
		p.set_value(result);
	}
}

auto compute_in_thread(int num, int den) {
	std::promise<int> result_promise{};
	auto result_future = result_promise.get_future();
	std::thread t{compute, num, den, std::move(result_promise)};
	t.detach();
	return result_future;
}


int main() {
	auto result = compute_in_thread(10, 5);
	std::cout << "Result of 10/5: " << result.get() << '\n';

	try {
		auto result = compute_in_thread(1, 0);
		std::cout << "Result of 1/0: " << std::flush;
		std::cout << result.get() << '\n';
	} catch(std::logic_error const & e) {
		std::cout << "Oh no, an exception! " << e.what();
	}
}
