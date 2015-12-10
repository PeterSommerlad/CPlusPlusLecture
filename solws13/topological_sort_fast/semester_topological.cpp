#include "semester_topological.h"
#include "module.h"
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <unordered_map>

namespace {

void depth_first_search(module_ptr m, modules & topological_order, std::unordered_map<module_ptr, bool> & marked_modules) {
	marked_modules[m] = true;
	auto successors = m->successors();
	std::for_each(std::begin(successors), std::end(successors), [&](module_ptr s){
		if (!marked_modules[s]) {
			depth_first_search(s, topological_order, marked_modules);
		}
	});
	topological_order.push_back(m);
}

modules topological_order(modules const & initial_set, modules const & all_modules) {
	std::unordered_map<module_ptr, bool> marked_modules{all_modules.size()};
	std::for_each(std::begin(all_modules), std::end(all_modules), [&](module_ptr m){
		marked_modules[m] = false;
	});
	modules topological_order{};
	std::for_each(std::begin(initial_set), std::end(initial_set), [&](module_ptr m){
		if (!marked_modules[m]) {
			depth_first_search(m, topological_order, marked_modules);
		}
	});
	return topological_order;
}

void update_successors(module_ptr module) {
	auto successors = module->successors();
	std::for_each(std::begin(successors), std::end(successors), [&](module_ptr s){
		s->update_earliest_semester(module->get_earliest_semester() + 1);
	});
}

void update_earliest_semester(module_catalog const & catalog) {
	auto all_modules = values(catalog);
	modules first_semester_modules{};
	std::for_each(std::begin(all_modules), std::end(all_modules), [&](module_ptr m){
		if(!m->has_predecessor()) {
			m->update_earliest_semester(1);
			first_semester_modules.push_back(m);
		}
	});

	auto complete_topological_order = topological_order(first_semester_modules, all_modules);
	std::for_each(std::rbegin(complete_topological_order), std::rend(complete_topological_order), [](module_ptr m) {
		update_successors(m);
	});
}

struct semester_comparator
{
    bool operator() ( module_ptr m, unsigned semester ) const
    {
        return m->get_earliest_semester() < semester;
    }

    bool operator() ( unsigned semester, module_ptr m ) const
    {
        return semester < m->get_earliest_semester();
    }
};

}


void print_semester_topological(std::istream & input, std::ostream& out) {
	auto catalog = read_modules(input);
	update_earliest_semester(catalog);
	auto modules = values(catalog);
	std::sort(std::begin(modules), std::end(modules), [](module_ptr lhs, module_ptr rhs) {
		return lhs->get_earliest_semester() < rhs->get_earliest_semester();
	});

	auto last_semester = (*std::rbegin(modules))->get_earliest_semester();
	for (auto semester = 1u; semester <= last_semester; semester++) {
		auto range = std::equal_range(std::begin(modules), std::end(modules), semester, semester_comparator{});
		out << semester << ": ";
		std::copy(range.first, range.second, std::ostream_iterator<module_ptr>{out, " "});
		out << "\n";
	}
}


