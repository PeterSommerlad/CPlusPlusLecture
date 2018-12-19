#include "Rectangle.h"
#include <stdexcept>
#include <string>

namespace Gardening {

const unsigned Rectangle::requiredPegs = 4;
const std::string Rectangle::name = "Rectangle";

Rectangle::Rectangle(double sideA, double sideB) :
		Shape { name }, sideA { sideA }, sideB { sideB } {
	if (sideA <= 0.0 || sideB <= 0.0) {
		throw std::invalid_argument{"Side lengths of a rectangle must not be zero or below."};
	}
}

unsigned Rectangle::pegs() const {
	return requiredPegs;
}

double Rectangle::ropes() const {
	return 2 * (sideA + sideB);
}

double Rectangle::seeds() const {
	return sideA * sideB * seedPerSquareMeter;
}

}
