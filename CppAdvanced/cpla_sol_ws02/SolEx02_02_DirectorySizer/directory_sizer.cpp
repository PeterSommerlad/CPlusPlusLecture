#include <iostream>
#include <experimental/filesystem>
#include <algorithm>
#include <iterator>
#include <vector>

namespace fs = std::experimental::filesystem;

unsigned directory_size(fs::path directory_path) {
	unsigned size { };

	for (auto const p : fs::directory_iterator(directory_path)) {
		if (is_directory(p)) {
			size += directory_size(p);
		} else {
			try {
				size += fs::file_size(p);
			} catch (...) {
				//ignore if size is not available
			}
		}
	}
	return size;
}

void print_directory_size(std::ostream & out, fs::path const directory_path) {
	out << "Size of directory " << directory_path << " " << directory_size(directory_path) << " byte\n";
}

void run_directory_size_printer(std::ostream & out, int const argc, char const * const * argv) {
	std::vector<fs::path> paths_to_print{};
	if (argc <= 1) {
		paths_to_print.push_back("./");
	} else {
		for (auto index = 1; index < argc; index++) {
			paths_to_print.push_back(argv[index]);
		}
	}
	for_each(begin(paths_to_print), end(paths_to_print), [&](auto path) {
		print_directory_size(out, path);
	});
}

int main(int argc, char **argv) {
	run_directory_size_printer(std::cout, argc, argv);
}
