#include "PolymorphismSuite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Shapes.h"

namespace{

void circlePegs() {
	Gardening::Circle bed(1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(1, shape.pegs());
}

void circleRopes(){
	Gardening::Circle bed(1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL_DELTA(7.28, shape.ropes(), 0.01);
}

void circleSeeds(){
	Gardening::Circle bed(1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL_DELTA(0.314, shape.seeds(), 0.001);
}

void diamondPegs() {
	Gardening::Diamond bed(1.0, 60.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(4, shape.pegs());
}

void diamondRopes() {
	Gardening::Diamond bed(1.0, 60.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(4.0, shape.ropes());
}

void diamondSeeds() {
	Gardening::Diamond bed(1.0, 60.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL_DELTA(0.0866, shape.seeds(), 0.0001);
}

void simpleEllipsePegs() {
	Gardening::Ellipse bed(2.0, 1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(2, shape.pegs());
}

void simpleEllipseRopes(){
	Gardening::Ellipse bed(2.0, 1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL_DELTA(14.93, shape.ropes(), 0.01);
}

void simpleEllipseSeeds(){
	Gardening::Ellipse bed(2.0, 1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL_DELTA(0.628, shape.seeds(), 0.001);
}

void rectanglePegs() {
	Gardening::Rectangle bed(2.0, 1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(4, shape.pegs());
}

void rectangleRopes() {
	Gardening::Rectangle bed(2.0, 1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(6.0, shape.ropes());
}

void rectangleSeeds() {
	Gardening::Rectangle bed(2.0, 1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(0.2, shape.seeds());
}

void simpleSquarePegs() {
	Gardening::Square bed(2.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(4, shape.pegs());
}

void simpleSquareRopes() {
	Gardening::Square bed(2.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(8.0, shape.ropes());
}

void simpleSquareSeeds() {
	Gardening::Square bed(2.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(0.4, shape.seeds());
}

void trianglePegs() {
	Gardening::Triangle bed(1.0, 1.0, 1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(3, shape.pegs());
}

void triangleRopes() {
	Gardening::Triangle bed(1.0, 1.0, 1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL(3.0, shape.ropes());
}

void triangleSeeds() {
	Gardening::Triangle bed(1.0, 1.0, 1.0);
	Gardening::Shape & shape = bed;
	ASSERT_EQUAL_DELTA(0.0433, shape.seeds(), 0.0001);
}

}

cute::suite make_suite_PolymorphismSuite(){
	cute::suite s;
	s.push_back(CUTE(circlePegs));
	s.push_back(CUTE(circleRopes));
	s.push_back(CUTE(circleSeeds));
	s.push_back(CUTE(diamondPegs));
	s.push_back(CUTE(diamondRopes));
	s.push_back(CUTE(diamondSeeds));
	s.push_back(CUTE(simpleEllipsePegs));
	s.push_back(CUTE(simpleEllipseRopes));
	s.push_back(CUTE(simpleEllipseSeeds));
	s.push_back(CUTE(rectanglePegs));
	s.push_back(CUTE(rectangleRopes));
	s.push_back(CUTE(rectangleSeeds));
	s.push_back(CUTE(simpleSquarePegs));
	s.push_back(CUTE(simpleSquareRopes));
	s.push_back(CUTE(simpleSquareSeeds));
	s.push_back(CUTE(trianglePegs));
	s.push_back(CUTE(triangleRopes));
	s.push_back(CUTE(triangleSeeds));

	return s;
}



