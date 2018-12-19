#include "Square.h"
#include <stdexcept>
#include <string>

namespace Gardening {

const unsigned Square::requiredPegs = 4;
const unsigned Square::numberOfSides = 4;
const std::string Square::name = "Square";

Square::Square(double side) :
		Shape { name }, side { side } {
	if (side <= 0.0) {
		throw std::invalid_argument{"Side length of a square must not be zero or below."};
	}
}

unsigned Square::pegs() const {
	return requiredPegs;
}

double Square::ropes() const {
	return numberOfSides * side;
}

double Square::seeds() const {
	return side * side * seedPerSquareMeter;
}

}
