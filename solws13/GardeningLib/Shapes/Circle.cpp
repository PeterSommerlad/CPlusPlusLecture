#include "Circle.h"
#include <stdexcept>
#include <string>

namespace Gardening {

unsigned const Circle::requiredPegs = 1;
std::string const Circle::name = "Circle";

Circle::Circle(double radius) :
		Shape { name }, radius { radius } {
	if (radius <= 0.0) {
		throw std::invalid_argument{"Radius must not be zero or below."};
	}
}

unsigned Circle::pegs() const {
	return requiredPegs;
}

double Circle::seeds() const {
	return radius * radius * pi * seedPerSquareMeter;
}

double Circle::ropes() const {
	double const ropeForConstruction = radius;
	double const perimeter { 2.0 * radius * pi};
	return perimeter + ropeForConstruction;
}

}
