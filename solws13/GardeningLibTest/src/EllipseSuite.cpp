#include "EllipseSuite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Shapes/Ellipse.h"

namespace{

void simpleEllipsePrint() {
	Gardening::Ellipse bed(2.0, 1.0);
	std::ostringstream result { };
	bed.print(result);
	ASSERT_EQUAL("Ellipse 2 14.9346 0.628319", result.str());
}

void simpleEllipsePegs() {
	Gardening::Ellipse bed(2.0, 1.0);
	ASSERT_EQUAL(2, bed.pegs());
}

void simpleEllipseRopes(){
	Gardening::Ellipse bed(2.0, 1.0);
	ASSERT_EQUAL_DELTA(14.93, bed.ropes(), 0.01);
}

void smallEllipseRopes(){
	Gardening::Ellipse bed(0.5,0.3);
	ASSERT_EQUAL_DELTA(3.89, bed.ropes(), 0.01);
}

void largeEllipseRopes(){
	Gardening::Ellipse bed(68.7, 35.9);
	ASSERT_EQUAL_DELTA(517.7, bed.ropes(), 0.1);
}

void simpleEllipseSeeds(){
	Gardening::Ellipse bed(2.0, 1.0);
	ASSERT_EQUAL_DELTA(0.628, bed.seeds(), 0.001);
}

void smallEllipseSeeds(){
	Gardening::Ellipse bed(0.5,0.3);
	ASSERT_EQUAL_DELTA(0.047, bed.seeds(), 0.001);
}

void largeEllipseSeeds(){
	Gardening::Ellipse bed(68.7, 35.9);
	ASSERT_EQUAL_DELTA(774.8, bed.seeds(), 0.1);
}

void zeroSemiMajorAxis() {
	ASSERT_THROWS(Gardening::Ellipse(0, 1.5), std::invalid_argument);
}

void negativeSemiMajorAxis() {
	ASSERT_THROWS(Gardening::Ellipse(-2.5, 1.5), std::invalid_argument);
}

void zeroSemiMinorAxis() {
	ASSERT_THROWS(Gardening::Ellipse(4.3, 0), std::invalid_argument);
}

void negativeSemiMinroAxis() {
	ASSERT_THROWS(Gardening::Ellipse(4.3, -2.8), std::invalid_argument);
}

void minorAxisLargerThanMajorAxis(){
	ASSERT_THROWS(Gardening::Ellipse(1.6, 2.4), std::invalid_argument);
}


}

cute::suite make_suite_EllipseSuite(){
	cute::suite s;
	s.push_back(CUTE(simpleEllipsePrint));
	s.push_back(CUTE(simpleEllipsePegs));
	s.push_back(CUTE(simpleEllipseRopes));
	s.push_back(CUTE(smallEllipseRopes));
	s.push_back(CUTE(largeEllipseRopes));
	s.push_back(CUTE(simpleEllipseSeeds));
	s.push_back(CUTE(smallEllipseSeeds));
	s.push_back(CUTE(largeEllipseSeeds));
	s.push_back(CUTE(zeroSemiMajorAxis));
	s.push_back(CUTE(negativeSemiMajorAxis));
	s.push_back(CUTE(zeroSemiMinorAxis));
	s.push_back(CUTE(negativeSemiMinroAxis));
	s.push_back(CUTE(minorAxisLargerThanMajorAxis));
	return s;
}



