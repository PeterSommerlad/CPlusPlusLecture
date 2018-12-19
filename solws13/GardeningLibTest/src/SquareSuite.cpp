#include "SquareSuite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Shapes/Square.h"
#include<stdexcept>

namespace {

void simpleSquarePrint() {
	Gardening::Square bed(2.0);
	std::ostringstream result { };
	bed.print(result);
	ASSERT_EQUAL("Square 4 8 0.4", result.str());
}

void simpleSquarePegs() {
	Gardening::Square bed(2.0);
	ASSERT_EQUAL(4, bed.pegs());
}

void simpleSquareRopes() {
	Gardening::Square bed(2.0);
	ASSERT_EQUAL(8.0, bed.ropes());
}

void simpleSquareSeeds() {
	Gardening::Square bed(2.0);
	ASSERT_EQUAL(0.4, bed.seeds());
}

void negativeSideLength() {
	ASSERT_THROWS(Gardening::Square(-1.0), std::invalid_argument);
}

void zeroSideLength() {
	ASSERT_THROWS(Gardening::Square(0.0), std::invalid_argument);
}

void smallSquareRopes(){
	Gardening::Square bed(0.1);
	ASSERT_EQUAL(0.4, bed.ropes());
}

void smallSquareSeeds(){
	Gardening::Square bed(0.1);
	ASSERT_EQUAL(0.001, bed.seeds());
}

void largeSquareRopes(){
	Gardening::Square bed(125.8);
	ASSERT_EQUAL(503.2, bed.ropes());
}

void largeSquareSeeds(){
	Gardening::Square bed(125.8);
	ASSERT_EQUAL(1582.564, bed.seeds());
}

void fractionalSideLengthRopes(){
	Gardening::Square bed(1.0/3.0);
	ASSERT_EQUAL_DELTA(4.0/3.0, bed.ropes(), 0.001);
}

void fractionalSideLengthSeeds(){
	Gardening::Square bed(1.0/3.0);
	ASSERT_EQUAL_DELTA(0.1/9.0, bed.seeds(), 0.001);
}
}

cute::suite make_suite_SquareSuite(){
	cute::suite s;
	s.push_back(CUTE(simpleSquarePrint));
	s.push_back(CUTE(simpleSquarePegs));
	s.push_back(CUTE(simpleSquareRopes));
	s.push_back(CUTE(smallSquareRopes));
	s.push_back(CUTE(largeSquareRopes));
	s.push_back(CUTE(fractionalSideLengthRopes));
	s.push_back(CUTE(simpleSquareSeeds));
	s.push_back(CUTE(smallSquareSeeds));
	s.push_back(CUTE(largeSquareSeeds));
	s.push_back(CUTE(fractionalSideLengthSeeds));
	s.push_back(CUTE(negativeSideLength));
	s.push_back(CUTE(zeroSideLength));
	return s;
}



