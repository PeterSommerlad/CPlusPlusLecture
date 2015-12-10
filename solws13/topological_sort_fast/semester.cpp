#include "semester.h"
#include "module.h"
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>
#include <ostream>
#include <fstream>

namespace {

template<typename ModItr>
bool can_be_taken(module_ptr module, ModItr accomplished_begin, ModItr accomplished_end) {
	auto predecessors = module->predecessors();
	return std::all_of(std::begin(predecessors), std::end(predecessors), [&](module_ptr m) {
		return std::find(accomplished_begin, accomplished_end, m) != accomplished_end;
	});
}

void print_plan(module_catalog const & catalog, std::ostream & out) {
	auto semester = 1u;
	modules finished_modules{};
	auto all_modules = values(catalog);
	modules remaining_modules{std::begin(all_modules), end(all_modules)};

	while (!remaining_modules.empty()) {
		out << semester << ": ";
		modules current_modules{};
		std::copy_if(std::begin(remaining_modules), std::end(remaining_modules), std::inserter(current_modules, std::begin(current_modules)), [&](module_ptr m){
			return can_be_taken(m, begin(finished_modules), end(finished_modules));
		});
		std::copy(std::begin(current_modules), std::end(current_modules), std::ostream_iterator<module_ptr>{out, " "});
		std::copy(std::begin(current_modules), std::end(current_modules), std::inserter(finished_modules, std::begin(finished_modules)));

		std::for_each(std::begin(current_modules), std::end(current_modules), [&](module_ptr m){
			remaining_modules.erase(std::remove(std::begin(remaining_modules), std::end(remaining_modules), m), std::end(remaining_modules));
		});

		semester++;
		out << "\n";
	}
}
}

void print_semester(std::string filename, std::ostream& out) {
	std::ifstream fstream{filename};
	auto catalog = read_modules(fstream);
	print_plan(catalog, out);
}
