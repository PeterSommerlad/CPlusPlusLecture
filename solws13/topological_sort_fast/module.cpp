#include "module.h"

#include <sstream>
#include <iterator>

module_ptr getModulePtr(std::string const & module_name, module_catalog & catalog) {
	if (catalog.count(module_name) == 0) {
		auto m = std::make_shared<module>(module_name);
		catalog[module_name] = m;
	}
	return catalog[module_name];
}

void add(module_catalog& catalog, std::string const & line) {
	std::stringstream line_stream{line};
	std::string module_name;
	line_stream >> module_name;
	auto module = getModulePtr(module_name, catalog);
	std::for_each(std::istream_iterator<std::string>{line_stream}, std::istream_iterator<std::string>{}, [&](std::string const & module_name){
		auto dependency = getModulePtr(module_name, catalog);
		module->add_predecessor(dependency);
	});
}

module_catalog read_modules(std::istream & input) {
	module_catalog catalog{};
	std::string line;
	while (getline(input, line)) {
		add(catalog, line);
	}
	return catalog;
}

