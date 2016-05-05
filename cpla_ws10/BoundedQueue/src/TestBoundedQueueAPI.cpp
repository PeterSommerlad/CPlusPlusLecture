#include "TestBoundedQueueAPI.h"
#include "BoundedQueue.h"
#include "cute.h"


void testConstructor(){
	ASSERTM("start writing tests", false);
}


void thisIsATestBoundedQueueAPITest() {
	ASSERTM("start writing tests", false);	
}

cute::suite make_suite_TestBoundedQueueAPI(){
	cute::suite s;
	s.push_back(CUTE(thisIsATestBoundedQueueAPITest));
	s.push_back(CUTE(testConstructor));
	return s;
}



