#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "CircleSuite.h"
#include "Shapes/Circle.h"
#include<string>
#include<sstream>

namespace{


void simpleCirclePrint() {
	Gardening::Circle bed(1.0);
	std::ostringstream result;
	bed.print(result);
	ASSERT_EQUAL("Circle 1 7.28319 0.314159", result.str());
}

void simpleCirclePegs() {
	Gardening::Circle bed(1.0);
	ASSERT_EQUAL(1, bed.pegs());
}

void simpleCircleRopes(){
	Gardening::Circle bed(1.0);
	ASSERT_EQUAL_DELTA(7.28, bed.ropes(), 0.01);
}

void smallCircleRopes(){
	Gardening::Circle bed(0.2);
	ASSERT_EQUAL_DELTA(1.45, bed.ropes(), 0.01);
}

void largeCircleRopes(){
	Gardening::Circle bed(157.3);
	ASSERT_EQUAL_DELTA(1145.6, bed.ropes(), 0.1);
}

void simpleCircleSeeds(){
	Gardening::Circle bed(1.0);
	ASSERT_EQUAL_DELTA(0.314, bed.seeds(), 0.001);
}

void smallCircleSeeds(){
	Gardening::Circle bed(0.2);
	ASSERT_EQUAL_DELTA(0.013, bed.seeds(), 0.001);
}

void largeCircleSeeds(){
	Gardening::Circle bed(157.3);
	ASSERT_EQUAL_DELTA(7773.3, bed.seeds(), 0.1);
}

void zeroRadius() {
	ASSERT_THROWS(Gardening::Circle(0.0), std::invalid_argument);
}

void negativeRadius() {
	ASSERT_THROWS(Gardening::Circle(-2.5), std::invalid_argument);
}

}

cute::suite make_suite_CircleSuite(){
	cute::suite s;
	s.push_back(CUTE(simpleCirclePrint));
	s.push_back(CUTE(simpleCirclePegs));
	s.push_back(CUTE(simpleCircleRopes));
	s.push_back(CUTE(smallCircleRopes));
	s.push_back(CUTE(largeCircleRopes));
	s.push_back(CUTE(simpleCircleSeeds));
	s.push_back(CUTE(smallCircleSeeds));
	s.push_back(CUTE(largeCircleSeeds));
	s.push_back(CUTE(zeroRadius));
	s.push_back(CUTE(negativeRadius));

	return s;
}



