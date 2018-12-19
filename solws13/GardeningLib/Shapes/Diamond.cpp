#include "Diamond.h"
#include <cmath>
#include <stdexcept>
#include <string>

namespace Gardening {

const unsigned Diamond::requiredPegs = 4;
const unsigned Diamond::numberOfSides = 4;
const std::string Diamond::name = "Diamond";
const double degreesOfHalfcircle = 180.0;

double Diamond::convertToRad(double deg) {
	return deg * pi / degreesOfHalfcircle;
}

Diamond::Diamond(double sideLength, double angleDegrees) :
		Shape { name }, sideLength { sideLength }, angle { convertToRad(angleDegrees) } {
	if (angleDegrees <= 0.0 || angleDegrees >= degreesOfHalfcircle) {
		throw std::invalid_argument{"The angle of a diamond must be between 0 and 180 degrees."};
	}
	if (sideLength <= 0.0) {
		throw std::invalid_argument{"Side length of a diamond must not be zero or below."};
	}
}

unsigned Diamond::pegs() const {
	return requiredPegs;
}

double Diamond::ropes() const {
	return numberOfSides * sideLength;
}

double Diamond::seeds() const {
	return sideLength * sideLength * std::sin(angle) * seedPerSquareMeter;
}

}
