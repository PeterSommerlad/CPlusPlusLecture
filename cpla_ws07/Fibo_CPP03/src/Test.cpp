#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "Fibo.h"

void testFibo0_is_0() {
	constexpr auto fib = Fibo<0>::value; // avoid ODR use
	ASSERT_EQUAL(0,fib);
}

void testFibo1_is_1() {
	constexpr auto fib = Fibo<1>::value; // avoid ODR use
	ASSERT_EQUAL(1,fib);
}

void testFibo2_is_1() {
	constexpr auto fib = Fibo<2>::value; // avoid ODR use
	ASSERT_EQUAL(1,fib);
}

void testFibo3_is_2() {
	constexpr auto fib = Fibo<3>::value; // avoid ODR use
	ASSERT_EQUAL(2,fib);
}

void testFibo10_is_55() {
	constexpr auto fib = Fibo<10>::value; // avoid ODR use
	ASSERT_EQUAL(55,fib);
}

void testFibo46_is_X() {
	constexpr auto fib = Fibo<46>::value; // avoid ODR use
	ASSERT_EQUAL(1836'311'903,fib);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testFibo0_is_0));
	s.push_back(CUTE(testFibo1_is_1));
	s.push_back(CUTE(testFibo2_is_1));
	s.push_back(CUTE(testFibo3_is_2));
	s.push_back(CUTE(testFibo10_is_55));
	s.push_back(CUTE(testFibo46_is_X));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



