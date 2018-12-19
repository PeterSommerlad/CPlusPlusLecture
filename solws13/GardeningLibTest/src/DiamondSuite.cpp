#include "DiamondSuite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Shapes/Diamond.h"


namespace {

void simpleDiamondPrint() {
	Gardening::Diamond bed(1.0, 60.0);
	std::ostringstream result { };
	bed.print(result);
	ASSERT_EQUAL("Diamond 4 4 0.0866025", result.str());
}

void simpleDiamondPegs() {
	Gardening::Diamond bed(1.0, 60.0);
	ASSERT_EQUAL(4, bed.pegs());
}

void simpleDiamondRopes() {
	Gardening::Diamond bed(1.0, 60.0);
	ASSERT_EQUAL(4.0, bed.ropes());
}

void simpleDiamondSeeds() {
	Gardening::Diamond bed(1.0, 60.0);
	ASSERT_EQUAL_DELTA(0.0866, bed.seeds(), 0.0001);
}

void negativeSize() {
	ASSERT_THROWS(Gardening::Diamond(-1.0, 60.0), std::invalid_argument);
}

void zeroSize() {
	ASSERT_THROWS(Gardening::Diamond(0.0, 60.0), std::invalid_argument);
}

void negaiveAngle() {
	ASSERT_THROWS(Gardening::Diamond(1.0, -60.0), std::invalid_argument);
}

void zeroAngle() {
	ASSERT_THROWS(Gardening::Diamond(1.0, 0.0), std::invalid_argument);
}

void halfcircleAngle() {
	ASSERT_THROWS(Gardening::Diamond(1.0, 180.0), std::invalid_argument);
}

void tooLargeAngle() {
	ASSERT_THROWS(Gardening::Diamond(1.0, 250.0), std::invalid_argument);
}

void smallAngleSeeds() {
	Gardening::Diamond bed(1.0, 0.5);
	ASSERT_EQUAL_DELTA(0.00087, bed.seeds(), 0.00001);
}

void largeAngleSeeds() {
	Gardening::Diamond bed(1.0, 179.5);
	ASSERT_EQUAL_DELTA(0.00087, bed.seeds(), 0.00001);
}

void rightAngleSeeds() {
	Gardening::Diamond bed(1.0, 90);
	ASSERT_EQUAL_DELTA(0.1, bed.seeds(), 0.00001);
}

void smallDiamondRopes() {
	Gardening::Diamond bed(0.1, 60.0);
	ASSERT_EQUAL(0.4, bed.ropes());
}

void smallDiamondSeeds() {
	Gardening::Diamond bed(0.1, 60.0);
	ASSERT_EQUAL_DELTA(0.00087, bed.seeds(), 0.00001);
}

void largeDiamondRopes() {
	Gardening::Diamond bed(150, 60.0);
	ASSERT_EQUAL(600.0, bed.ropes());
}

void largeDiamondSeeds() {
	Gardening::Diamond bed(150, 60.0);
	ASSERT_EQUAL_DELTA(1948.5, bed.seeds(), 0.1);
}
}

cute::suite make_suite_DiamondSuite(){
	cute::suite s;
	s.push_back(CUTE(simpleDiamondPrint));
	s.push_back(CUTE(simpleDiamondPegs));
	s.push_back(CUTE(simpleDiamondRopes));
	s.push_back(CUTE(smallDiamondRopes));
	s.push_back(CUTE(largeDiamondRopes));
	s.push_back(CUTE(simpleDiamondSeeds));
	s.push_back(CUTE(smallDiamondSeeds));
	s.push_back(CUTE(largeDiamondSeeds));
	s.push_back(CUTE(negativeSize));
	s.push_back(CUTE(zeroSize));
	s.push_back(CUTE(negaiveAngle));
	s.push_back(CUTE(zeroAngle));
	s.push_back(CUTE(halfcircleAngle));
	s.push_back(CUTE(tooLargeAngle));
	s.push_back(CUTE(smallAngleSeeds));
	s.push_back(CUTE(largeAngleSeeds));
	s.push_back(CUTE(rightAngleSeeds));
	return s;
}



