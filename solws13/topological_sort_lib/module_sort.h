#ifndef SRC_MODULE_SORT_H_
#define SRC_MODULE_SORT_H_
#include "module.h"
#include <set>

using level_result = std::vector<module::spm>;
struct deep_name_compare{
bool operator()(spm const &l, spm const &r){
	if (l && r){
		return *l < *r;
	}
	return (!l && r);
}
};

struct module_sort{
	std::set<module::spm,deep_name_compare> all_modules;

	explicit module_sort(std::istream &is){
		read(is);
	}
	auto size() const {
		return all_modules.size();
	}

	void read(std::istream& input);
	module::spm insert_or_update_module(const std::string& name);
	level_result next_level();
};

void print_semester_topological(std::istream &input, std::ostream& out);

#endif /* SRC_MODULE_SORT_H_ */
