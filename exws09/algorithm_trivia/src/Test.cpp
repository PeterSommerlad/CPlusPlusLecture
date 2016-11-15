#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "numeric_algorithms.h"
#include "property_checking_algorithms.h"
#include "copy_and_replace_algorithms.h"
#include "find_algorithms.h"
#include "remove_unique_rotate_algorithms.h"
#include "fill_and_generate_algorithms.h"
#include "partition_algorithms.h"
#include "sort_algorithms.h"
#include "sorted_sequence_algorithms.h"
#include "set_algorithms.h"
#include "heap_algorithms.h"
#include "min_max_algorithms.h"


bool runAllTests(int argc, char const *argv[]) {

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(make_suite_numeric_algorithms(), "Numeric Algorithms");
	success &= runner(make_suite_property_checking_algorithms(), "Property Checking Algorithms");
	success &= runner(make_suite_find_algorithms(), "Find Algorithms");
	success &= runner(make_suite_copy_and_replace_algorithms(), "Copy and Replace Algorithms");
	success &= runner(make_suite_remove_unique_rotate_algorithms(), "Remove, Unique and Rotate Algorithms");
	success &= runner(make_suite_fill_and_generate_algorithms(), "Fill and Generate Algorithms");
	success &= runner(make_suite_partition_algorithms(), "Partition Algorithms");
	success &= runner(make_suite_sort_algorithms(), "Sort Algorithms");
	success &= runner(make_suite_sorted_sequence_algorithms(), "Sorted Sequence Algorithms");
	success &= runner(make_suite_set_algorithms(), "Set Algorithms");
	success &= runner(make_suite_heap_algorithms(), "Heap Algorithms");
	success &= runner(make_suite_min_max_algorithms(), "Min-Max Algorithms");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
