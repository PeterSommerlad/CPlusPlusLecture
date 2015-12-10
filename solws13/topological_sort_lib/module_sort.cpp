#include "module_sort.h"
#include <sstream>

level_result module_sort::next_level() {
	std::vector<module::spm> result { };
	copy_if(begin(all_modules), end(all_modules), back_inserter(result), [](const spm& p) {
		return bool(p) && p->is_ready();
	});
	for (module::spm p : result) {
		for (module::spm m : all_modules) {
			if (m)
				m->done_with(p);
		}
		all_modules.erase(p);
	}
	sort(begin(result), end(result), deep_name_compare { });
	return result;
}

module::spm module_sort::insert_or_update_module(const std::string& name) {
	auto current = make_module(name);
	auto mod_it = all_modules.find(current);
	if (mod_it != all_modules.end()) {
		current = *mod_it;
	} else {
		all_modules.insert(current);
	}
	return current;
}

void module_sort::read(std::istream& input) {
	std::string line;
	while (std::getline(input, line)) {
		std::istringstream is { line };
		std::string name;
		if (is >> name) {
			auto current = insert_or_update_module(name);
			while (is >> name) {
				auto dep = insert_or_update_module(name);
				current->add(dep);
			}
		}
	}
}
void print_semester_topological(std::istream &input, std::ostream& out){
	module_sort ms{input};
	unsigned level{1};
	std::ostream_iterator<std::string> oi{out," "};
	while (ms.size()){
		auto res = ms.next_level();
		out << level++ << ": ";
		transform(begin(res),end(res),oi,[](module::spm p){return p?p->name:"";});
		out << '\n';
	}
}
