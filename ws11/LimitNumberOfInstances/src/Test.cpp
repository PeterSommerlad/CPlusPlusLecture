#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "LimitNumberOfInstances.h"
class one:LimitNofInstances<one,1>{ /*...*/};
void testOnlyOne() {
	one theOne;
	ASSERT_THROWS(one(),std::logic_error);
	ASSERT_THROWS(one(theOne),std::logic_error);
}

void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testOnlyOne));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
}



