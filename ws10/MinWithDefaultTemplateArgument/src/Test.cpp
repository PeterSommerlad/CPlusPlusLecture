#include "MyMin.h"
#include "MyMax.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

void testMyMinCompiles() {
	ASSERT_EQUAL(42,MyMin::min(42,43.0));
// fails to compile:	ASSERT_EQUAL(42,std::min(42,43.0));
}
void testMyMaxCompiles(){
	ASSERT_EQUAL(42,MyMax::max(21.0f,42));
//	ASSERT_EQUAL(42,std::max(21.0f,42));
}

void testMyMinBadResults(){
	using namespace MyMinBad;
	ASSERT_EQUAL(0.1,min(0.1,'a'));
	ASSERT_EQUAL(0.1,min<double>('a',0.1));
	//ASSERT_EQUAL(0.1,min('a',0.1));// fails: min<char,double>
}
void testMyMinGoodResults(){
	using namespace MyMin; // return type deduction with decltype
	ASSERT_EQUAL(0.1,min(0.1,'a'));
	ASSERT_EQUAL(0.1,min('a',0.1));
}


void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testMyMinCompiles));
	s.push_back(CUTE(testMyMaxCompiles));
	s.push_back(CUTE(testMyMinBadResults));
	s.push_back(CUTE(testMyMinGoodResults));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}



