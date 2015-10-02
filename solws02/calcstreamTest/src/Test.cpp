#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "calcstream.h"

void testaddition() {
	std::istringstream in{"5 + 4"};
	ASSERT_EQUAL(9,calc(in));
}
void testsubtraction() {
	std::istringstream in{"5 - 4"};
	ASSERT_EQUAL(1,calc(in));
}
void testmultiplication() {
	std::istringstream in{"5 * 4"};
	ASSERT_EQUAL(20,calc(in));
}
void testdivision() {
	std::istringstream in{"25 / 4"};
	ASSERT_EQUAL(6,calc(in));
}
void testmodulo() {
	std::istringstream in{"5 % 4"};
	ASSERT_EQUAL(1,calc(in));
}
void testemptyInput(){
	std::istringstream in{};
	ASSERT_EQUAL(0,calc(in));
}


void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testaddition));
	s.push_back(CUTE(testsubtraction));
	s.push_back(CUTE(testmultiplication));
	s.push_back(CUTE(testdivision));
	s.push_back(CUTE(testmodulo));
	s.push_back(CUTE(testemptyInput));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}



