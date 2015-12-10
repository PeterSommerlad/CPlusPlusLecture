#include "rotate3arguments.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

void rotate3ints(){
	int a{1};
	int b{2};
	int c{3};
	rotate3arguments(a,b,c);
	ASSERT_EQUAL(1,c);
	ASSERT_EQUAL(2,a);
	ASSERT_EQUAL(3,b);
}

void rotate3strings(){
	auto a="one";
	auto b="two";
	auto c="three";
	rotate3arguments(a,b,c);
	ASSERT_EQUAL("one",c);
	ASSERT_EQUAL("two",a);
	ASSERT_EQUAL("three",b);
}



void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(rotate3ints));
	s.push_back(CUTE(rotate3strings));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}



