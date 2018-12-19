#include "RectangleSuite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Shapes/Rectangle.h"

namespace {

void simpleRectanglePrint() {
	Gardening::Rectangle bed(2.0, 1.0);
	std::ostringstream result { };
	bed.print(result);
	ASSERT_EQUAL("Rectangle 4 6 0.2", result.str());
}

void simpleRectanglePegs() {
	Gardening::Rectangle bed(2.0, 1.0);
	ASSERT_EQUAL(4, bed.pegs());
}

void simpleRectangleRopes() {
	Gardening::Rectangle bed(2.0, 1.0);
	ASSERT_EQUAL(6.0, bed.ropes());
}

void simpleRectangleSeeds() {
	Gardening::Rectangle bed(2.0, 1.0);
	ASSERT_EQUAL(0.2, bed.seeds());
}

void negativeSideALength() {
	ASSERT_THROWS(Gardening::Rectangle(-1.0, 1.0), std::invalid_argument);
}

void negativeSideBLength() {
	ASSERT_THROWS(Gardening::Rectangle(1.0, -1.0), std::invalid_argument);
}

void zeroSideALength() {
	ASSERT_THROWS(Gardening::Rectangle(0.0, 1.0), std::invalid_argument);
}

void zeroSideBLength() {
	ASSERT_THROWS(Gardening::Rectangle(1.0, 0.0), std::invalid_argument);
}

void smallRectangleRopes(){
	Gardening::Rectangle bed(0.1, 0.2);
	ASSERT_EQUAL(0.6, bed.ropes());
}

void smallRectangleSeeds(){
	Gardening::Rectangle bed(0.1, 0.2);
	ASSERT_EQUAL(0.002, bed.seeds());
}

void largeRectangleRopes(){
	Gardening::Rectangle bed(125.8, 75.6);
	ASSERT_EQUAL(402.8, bed.ropes());
}

void largeRectangleSeeds(){
	Gardening::Rectangle bed(125.8, 75.6);
	ASSERT_EQUAL(951.048, bed.seeds());
}

void fractionalSidesLengthRopes(){
	Gardening::Rectangle bed(1.0/3.0, 2.0/3.0);
	ASSERT_EQUAL_DELTA(2.0, bed.ropes(), 0.001);
}

void fractionalSidesLengthSeeds(){
	Gardening::Rectangle bed(1.0/3.0, 2.0/3.0);
	ASSERT_EQUAL_DELTA(0.2/9.0, bed.seeds(), 0.001);
}

}

cute::suite make_suite_RectangleSuite(){
	cute::suite s;
	s.push_back(CUTE(simpleRectanglePrint));
	s.push_back(CUTE(simpleRectanglePegs));
	s.push_back(CUTE(simpleRectangleRopes));
	s.push_back(CUTE(smallRectangleRopes));
	s.push_back(CUTE(largeRectangleRopes));
	s.push_back(CUTE(fractionalSidesLengthRopes));
	s.push_back(CUTE(simpleRectangleSeeds));
	s.push_back(CUTE(smallRectangleSeeds));
	s.push_back(CUTE(largeRectangleSeeds));
	s.push_back(CUTE(fractionalSidesLengthSeeds));
	s.push_back(CUTE(negativeSideALength));
	s.push_back(CUTE(negativeSideBLength));
	s.push_back(CUTE(zeroSideALength));
	s.push_back(CUTE(zeroSideBLength));
	return s;
}



