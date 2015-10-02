#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "calc.h"

void testaddition() {
	ASSERT_EQUAL(5,calc(2,3,'+'));
}
void testsubtraction() {
	ASSERT_EQUAL(5,calc(8,3,'-'));
}
void testmultiplication() {
	ASSERT_EQUAL(6,calc(2,3,'*'));
}
void testdivision() {
	ASSERT_EQUAL(4,calc(14,3,'/'));
}
void testmodulo() {
	ASSERT_EQUAL(5,calc(11,6,'%'));
}
void testdivisionByZero() {
	ASSERT_EQUAL(0,calc(2,0,'/'));
}
void testmoduloByZero() {
	ASSERT_EQUAL(0,calc(2,0,'%'));
}


void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testaddition));
	s.push_back(CUTE(testsubtraction));
	s.push_back(CUTE(testmultiplication));
	s.push_back(CUTE(testdivision));
	s.push_back(CUTE(testmodulo));
	s.push_back(CUTE(testdivisionByZero));
	s.push_back(CUTE(testmoduloByZero));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}



