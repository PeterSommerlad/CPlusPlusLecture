#include <vector>
#include <chrono>
#include <iostream>
#include <ostream>
#include <ios>
#include <iterator>
#include <algorithm>

bool find_with_loop(std::vector<int> const & values, int const v) {
	auto const end = std::end(values);
	for(auto it = std::begin(values); it != end; ++it) {
		if (*it == v) {
			return true;
		}
	}
	return false;
}

bool find_with_algorithm(std::vector<int> const & values, int const v) {
	auto const pos = std::find(std::begin(values), std::end(values), v);
	return pos != std::end(values);
}

void execute_measurement(std::vector<int> const & values, std::ostream & out) {
	out << std::boolalpha;

	auto const loop_start = std::chrono::high_resolution_clock::now();
	auto const loop_result = find_with_loop(values, 2);
	auto const loop_end = std::chrono::high_resolution_clock::now();
	auto const loop_duration = std::chrono::duration_cast<std::chrono::milliseconds>(loop_end - loop_start);
	out << "found with a loop: " << loop_result << " in " << loop_duration.count() << "ms" << std::endl;

	auto const algorithm_start = std::chrono::high_resolution_clock::now();
	auto const algorithm_result = find_with_algorithm(values, 2);
	auto const algorithm_end = std::chrono::high_resolution_clock::now();
	auto const algorithm_duration = std::chrono::duration_cast<std::chrono::milliseconds>(algorithm_end - algorithm_start);
	out << "found with an algorithm: " << algorithm_result << " in " << algorithm_duration.count() << "ms" << std::endl;
}

int main(int argc, char **argv) {
	std::vector<int> const values(100000000, 1);
	for (auto i = 0; i < 10; i++) {
		execute_measurement(values, std::cout);
	}
}

