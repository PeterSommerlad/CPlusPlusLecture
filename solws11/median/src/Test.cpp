#include "median.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <algorithm>
#include <vector>
void testmedianDouble() {
	ASSERT_EQUAL_DELTA(7.0 ,median(7.0, 7.1, 6.9), 0.0001);
}
void testmedianIntRightValue() {
	ASSERT_EQUAL(5, median(3,9,5));
}
void testmedianString(){
	ASSERT_EQUAL("four", median<std::string>("four","five","six"));
}
void testmedianCharPtr(){
	ASSERT_EQUAL("four", median("five","four","six"));
}
void testmedianAllIntPermutations() {
	std::vector<int> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(9);
	std::sort(v.begin(), v.end());
	int counter(0);
	do {
		ASSERT_EQUAL(5, median(v[0],v[1],v[2]));
		++counter;
	} while (std::next_permutation(v.begin(), v.end()));
	ASSERT_EQUAL(6,counter);
}


void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testmedianDouble));
	s.push_back(CUTE(testmedianIntRightValue));
	s.push_back(CUTE(testmedianString));
	s.push_back(CUTE(testmedianCharPtr));
	s.push_back(CUTE(testmedianAllIntPermutations));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}




