#include "dynArray.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "boost/iterator/counting_iterator.hpp"

#include <optional>
#include <string>



void defaultconstructdynArray() {
	dynArray<int> da { };	//Sol CPlA Ex02: Template argument cannot be omitted.
	ASSERT_EQUAL(0, da.size());
	ASSERT(da.empty());
}
void initializerlistconstructeddynArrayisNotEmpty() {
	dynArray da { 1u, 2u, 3u, 4u };	//Sol CPlA Ex02: Template argument can be omitted.
	ASSERT_EQUAL(4, da.size());
	ASSERT(!da.empty());
	ASSERT_EQUAL(1u, da[0]);
	ASSERT_EQUAL(4u, da[-1]);
	ASSERT_EQUAL(2, da[-3]);
	ASSERT_EQUAL(3, da[2]);
}

void rangeconstructeddynArray() {
	auto iter = boost::make_counting_iterator(0.0);
	auto e = boost::make_counting_iterator(11.0);
	dynArray const da(iter, e);	//Sol CPlA Ex02: Template argument can be omitted.
	ASSERT_EQUAL(11, da.size());
	ASSERT_EQUAL(1.0, da.at(1));
	ASSERT_EQUAL(10.0, da.at(-1));
	ASSERT_EQUAL(5.0, da[5]);
	ASSERT_EQUAL(6.0, da[-5]);
}
void n_times_value_constructeddynArray() {
	dynArray da(10u, 3.14);	//Sol CPlA Ex02: Template argument can be omitted.
	ASSERT_EQUAL(10u, da.size());
	ASSERT_EQUAL(3.14, da.at(-1));
}
void testtwoparaemterconstructorambiguity() {
	dynArray da(10u, 1u); // must use parentheses	//Sol CPlA Ex02: Template argument can be omitted.
	ASSERT_EQUAL(10u, da.size());
}

// the following is a lazy and bad test case, because it tests too much in one
void sequencecontainerfunctions() {
	dynArray da { 1, 2, 3 };	//Sol CPlA Ex02: Template argument can be omitted.
	da.push_back(4);
	ASSERT_EQUAL(4, da.size());
	ASSERT_EQUAL(1, da.front());
	ASSERT_EQUAL(4, da.back());
	da.front() = 42;
	ASSERT_EQUAL(42, da.front());
	da.back() = 42;
	ASSERT_EQUAL(42, da.back());
	da.pop_back();
	ASSERT_EQUAL(3, da.size());
}

void const_iterator_functions() {
	dynArray da { 'a', 'b', 'c' };	//Sol CPlA Ex02: Template argument can be omitted.
	std::string s { da.begin(), da.end() };
	ASSERT_EQUAL("abc", s);
}
void nonconst_iterator_functions() {
	dynArray da { "one", "two" };	//Sol CPlA Ex02: Template argument can be omitted.
	ASSERT_EQUAL("one", *da.begin());
	*da.begin() = "none";
	ASSERT_EQUAL("none", *da.begin());
	*(da.end() - 1) = "on";
	ASSERT_EQUAL("on", *(da.begin() + 1));
}
void reverse_iterator_functions() {
	dynArray da { '1', '2', '3', '4' };	//Sol CPlA Ex02: Template argument can be omitted.
	std::string s { da.rbegin(), da.rend() };
	ASSERT_EQUAL("4321", s);
}
void nonconst_reverse_iterator_functions() {
	dynArray da { 4, 3, 2, 1 };	//Sol CPlA Ex02: Template argument can be omitted.
	*da.rbegin() = 42;
	ASSERT_EQUAL(42, da.at(-1));
	*(da.rend() - 1) = 42;
	ASSERT_EQUAL(42, da[0]);
}

void const_iterator_functions_availability() {
	dynArray da { 'p', 'e', 't', 'e', 'r' };	//Sol CPlA Ex02: Template argument can be omitted.
	std::string peter { da.cbegin(), da.cend() };
	std::string retep { da.crbegin(), da.crend() };
	ASSERT_EQUAL("peter", peter);
	ASSERT_EQUAL("retep", retep);
}

void resizeAvailable() {
	dynArray<int> da { };	//Sol CPlA Ex02: Template argument cannot be omitted.
	da.resize(10);
	ASSERT_EQUAL(10, da.size());
	ASSERT_EQUAL(0, da[-1]);
}

void makedynArrayFactory() {
	auto da = make_dynArray( { 1.0, 2.0, 3.0 });
	ASSERT_EQUAL(3, da.size());
	ASSERT_EQUAL(3.0, da.at(-1));
}

//Sol CPlA Ex02: Test cases for pop_back() function returning std::optional<T>
void test_dynArray_pop_empty_container_returns_empty_optional() {
	dynArray<int> empty { };	//Sol CPlA Ex02: Template argument cannot be omitted.
	std::optional popped_value = empty.pop_back();
	ASSERTM("Popping an empty dynArray shall return an empty optional.", !popped_value.has_value());
}

void test_dynArray_pop_non_empty_container_returns_back_element() {
	dynArray values { "one", "two", "three" };	//Sol CPlA Ex02: Template argument can be omitted. Deduces to dynArray<char const *>
	std::optional popped_value = values.pop_back();
	ASSERT_EQUAL("three", popped_value.value());
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s;
	s.push_back(CUTE(defaultconstructdynArray));
	s.push_back(CUTE(initializerlistconstructeddynArrayisNotEmpty));
	s.push_back(CUTE(rangeconstructeddynArray));
	s.push_back(CUTE(sequencecontainerfunctions));
	s.push_back(CUTE(const_iterator_functions));
	s.push_back(CUTE(nonconst_iterator_functions));
	s.push_back(CUTE(reverse_iterator_functions));
	s.push_back(CUTE(nonconst_reverse_iterator_functions));
	s.push_back(CUTE(const_iterator_functions_availability));
	s.push_back(CUTE(resizeAvailable));
	s.push_back(CUTE(makedynArrayFactory));
	s.push_back(CUTE(n_times_value_constructeddynArray));
	s.push_back(CUTE(testtwoparaemterconstructorambiguity));
	s.push_back(CUTE(test_dynArray_pop_empty_container_returns_empty_optional));
	s.push_back(CUTE(test_dynArray_pop_non_empty_container_returns_back_element));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

