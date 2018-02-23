#include <iostream>


int main() {
	int intValue1 = 15;
	int intValue2 = 24;
	auto intIntSum = intValue1 + intValue2;

	long longValue1 = 11l;
	auto longIntSum = longValue1 + intValue1;

	double doubleValue = 128.0;
	auto doubleIntSum = doubleValue + intValue1;

	unsigned unsignedValue = 99u;
	auto unsignedIntSum = unsignedValue + intValue1;

	int index = 0;
	unsigned int size=0;

	if (index <= size-1) { // correct: index < size
		std::cout << "Error in exams, somwhere there is a non-solution copied from";
	} else {
		std::cout << "should be out of bounds";
	}
}
