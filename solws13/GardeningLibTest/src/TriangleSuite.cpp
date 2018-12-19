#include "TriangleSuite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Shapes/Triangle.h"
#include <stdexcept>

namespace {

void simpleTrianglePrint() {
	Gardening::Triangle bed(1.0, 1.0, 1.0);
	std::ostringstream result { };
	bed.print(result);
	ASSERT_EQUAL("Triangle 3 3 0.0433013", result.str());
}

void simpleTrianglePegs() {
	Gardening::Triangle bed(1.0, 1.0, 1.0);
	ASSERT_EQUAL(3, bed.pegs());
}

void simpleTriangleRopes() {
	Gardening::Triangle bed(1.0, 1.0, 1.0);
	ASSERT_EQUAL(3.0, bed.ropes());
}

void simpleTriangleSeeds() {
	Gardening::Triangle bed(1.0, 1.0, 1.0);
	ASSERT_EQUAL_DELTA(0.0433, bed.seeds(), 0.0001);
}

void negativeSideALength() {
	ASSERT_THROWS(Gardening::Triangle(-1.0, 1.0, 1.0), std::invalid_argument);
}

void negativeSideBLength() {
	ASSERT_THROWS(Gardening::Triangle(1.0, -1.0, 1.0), std::invalid_argument);
}

void negativeSideCLength() {
	ASSERT_THROWS(Gardening::Triangle(1.0, 1.0, -1.0), std::invalid_argument);
}

void zeroSideALength() {
	ASSERT_THROWS(Gardening::Triangle(0.0, 1.0, 1.0), std::invalid_argument);
}

void zeroSideBLength() {
	ASSERT_THROWS(Gardening::Triangle(1.0, 0.0, 1.0), std::invalid_argument);
}

void zeroSideCLength() {
	ASSERT_THROWS(Gardening::Triangle(1.0, 1.0, 0.0), std::invalid_argument);
}

void tooLongSideA(){
	ASSERT_THROWS(Gardening::Triangle(3.0, 1.0, 1.0), std::invalid_argument);
}

void tooLongSideB(){
	ASSERT_THROWS(Gardening::Triangle(1.0, 3.0, 1.0), std::invalid_argument);
}

void tooLongSideC(){
	ASSERT_THROWS(Gardening::Triangle(1.0, 1.0, 3.0), std::invalid_argument);
}

void twoDTriangle(){
	ASSERT_THROWS(Gardening::Triangle(1.0, 1.0, 2.0), std::invalid_argument);
}

void smallTriangleRopes() {
	Gardening::Triangle bed(0.15, 0.1, 0.2);
	ASSERT_EQUAL(0.45, bed.ropes());
}

void smallTriangleSeeds() {
	Gardening::Triangle bed(0.15, 0.1, 0.2);
	ASSERT_EQUAL_DELTA(0.00072, bed.seeds(), 0.00001);
}

void largeTriangleRopes(){
	Gardening::Triangle bed(150, 100, 200);
	ASSERT_EQUAL(450.0, bed.ropes());
}

void largeTriangleSeeds(){
	Gardening::Triangle bed(150, 100, 200);
	ASSERT_EQUAL_DELTA(726.18, bed.seeds(), 0.01);
}
}

cute::suite make_suite_TriangleSuite(){
	cute::suite s;
	s.push_back(CUTE(simpleTrianglePrint));
	s.push_back(CUTE(simpleTrianglePegs));
	s.push_back(CUTE(simpleTriangleRopes));
	s.push_back(CUTE(smallTriangleRopes));
	s.push_back(CUTE(largeTriangleRopes));
	s.push_back(CUTE(simpleTriangleSeeds));
	s.push_back(CUTE(smallTriangleSeeds));
	s.push_back(CUTE(largeTriangleSeeds));
	s.push_back(CUTE(negativeSideALength));
	s.push_back(CUTE(negativeSideBLength));
	s.push_back(CUTE(negativeSideCLength));
	s.push_back(CUTE(zeroSideALength));
	s.push_back(CUTE(zeroSideBLength));
	s.push_back(CUTE(zeroSideCLength));
	s.push_back(CUTE(tooLongSideA));
	s.push_back(CUTE(tooLongSideB));
	s.push_back(CUTE(tooLongSideC));
	s.push_back(CUTE(twoDTriangle));
	return s;
}



