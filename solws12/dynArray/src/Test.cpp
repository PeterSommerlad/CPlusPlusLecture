#include "dynArray.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "boost/iterator/counting_iterator.hpp"

void defaultconstructdynArray(){
	dynArray<int> da{};
	ASSERT_EQUAL(0,da.size());
	ASSERT(da.empty());
}
void initializerlistconstructeddynArrayisNotEmpty(){
	dynArray<unsigned> da{1u,2u,3u,4u};
	ASSERT_EQUAL(4,da.size());
	ASSERT(!da.empty());
	ASSERT_EQUAL(1u,da[0]);
	ASSERT_EQUAL(4u,da[-1]);
	ASSERT_EQUAL(2,da[-3]);
	ASSERT_EQUAL(3,da[2]);
}

void rangeconstructeddynArray(){
	auto iter=boost::make_counting_iterator(0.0);
	auto e=boost::make_counting_iterator(11.0);
	dynArray<double> const da(iter,e);
	ASSERT_EQUAL(11,da.size());
	ASSERT_EQUAL(1.0,da.at(1));
	ASSERT_EQUAL(10.0,da.at(-1));
	ASSERT_EQUAL(5.0,da[5]);
	ASSERT_EQUAL(6.0,da[-5]);
}
void n_times_value_constructeddynArray(){
	dynArray<double> da(10u,3.14);
	ASSERT_EQUAL(10u,da.size());
	ASSERT_EQUAL(3.14,da.at(-1));
}
void testtwoparaemterconstructorambiguity(){
	dynArray<size_t> da(10u,1u); // must use parentheses
	ASSERT_EQUAL(10u,da.size());
}

// the following is a lazy and bad test case, because it tests too much in one
void sequencecontainerfunctions(){
	dynArray<int> da{1,2,3};
	da.push_back(4);
	ASSERT_EQUAL(4,da.size());
	ASSERT_EQUAL(1,da.front());
	ASSERT_EQUAL(4,da.back());
	da.front()=42;
	ASSERT_EQUAL(42,da.front());
	da.back()=42;
	ASSERT_EQUAL(42,da.back());
	da.pop_back();
	ASSERT_EQUAL(3,da.size());
}

void const_iterator_functions(){
	dynArray<char> da{'a','b','c'};
	std::string s{da.begin(),da.end()};
	ASSERT_EQUAL("abc",s);
}
void nonconst_iterator_functions(){
	dynArray<std::string> da{"one","two"};
	ASSERT_EQUAL("one",*da.begin());
	*da.begin()="none";
	ASSERT_EQUAL("none",*da.begin());
	*(da.end()-1)="on";
	ASSERT_EQUAL("on",*(da.begin()+1));
}
void reverse_iterator_functions(){
	dynArray<char> da{'1','2','3','4'};
	std::string s{da.rbegin(),da.rend()};
	ASSERT_EQUAL("4321",s);
}
void nonconst_reverse_iterator_functions(){
	dynArray<int> da{4,3,2,1};
	*da.rbegin() = 42;
	ASSERT_EQUAL(42,da.at(-1));
	*(da.rend()-1) = 42;
	ASSERT_EQUAL(42,da[0]);
}

void const_iterator_functions_availability(){
	dynArray<char> da{'p','e','t','e','r'};
	std::string peter{da.cbegin(),da.cend()};
	std::string retep{da.crbegin(),da.crend()};
	ASSERT_EQUAL("peter",peter);
	ASSERT_EQUAL("retep",retep);
}

void resizeAvailable(){
	dynArray<int> da{};
	da.resize(10);
	ASSERT_EQUAL(10,da.size());
	ASSERT_EQUAL(0,da[-1]);
}

void makedynArrayFactory(){
	auto da=make_dynArray({1.0,2.0,3.0});
	ASSERT_EQUAL(3,da.size());
	ASSERT_EQUAL(3.0,da.at(-1));
}


void runAllTests(int argc, char const *argv[]){
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
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}


