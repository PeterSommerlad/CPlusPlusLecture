#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "squareroot.h"
#include <vector>
#include <stdexcept>



void testEmptyVectorAtThrows() {
	std::vector<int> empty_vector{};
	ASSERT_THROWS(empty_vector.at(0),std::out_of_range);
}






void testSquareRootNegativeThrows(){
	ASSERT_THROWS(square_root(-1.0),std::invalid_argument);
}







void testForExceptionTryCatch(){
	std::vector<int> empty_vector{};
	try {
		empty_vector.at(1);
		FAILM("expected Exception");
	}
	catch (std::out_of_range const&){} // expected
}


void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testEmptyVectorAtThrows));
	s.push_back(CUTE(testSquareRootNegativeThrows));
	s.push_back(CUTE(testForExceptionTryCatch));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}



