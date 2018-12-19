#include "Ellipse.h"
#include <cmath>
#include <stdexcept>
#include <string>

namespace Gardening {
const unsigned Ellipse::requiredPegs = 2;
const std::string Ellipse::name = "Ellipse";

Ellipse::Ellipse(double semiMajorAxis, double semiMinorAxis) :
		Shape { name }, semiMajorAxis { semiMajorAxis }, semiMinorAxis { semiMinorAxis } {
	if (semiMajorAxis <= 0.0 || semiMinorAxis <= 0.0) {
		throw std::invalid_argument{"Semiaxes of an ellipse must not be zero or below."};
	}
	if (semiMajorAxis < semiMinorAxis) {
		throw std::invalid_argument{"Semi-major axis of an ellipse must be larger than its semi-minor axis."};
	}
}

unsigned Ellipse::pegs() const {
	return requiredPegs;
}

double Ellipse::ropes() const {
	//Gaertnerkonstruktion (http://de.wikipedia.org/wiki/G%C3%A4rtnerkonstruktion)
	double const ropeForConstruction { semiMinorAxis + 2 * semiMajorAxis };
	//Approximation of perimeter: ~10% accuracy (http://de.wikipedia.org/wiki/Ellipse#Umfang)
	double const perimeter { pi * std::sqrt(2 * (semiMajorAxis * semiMajorAxis + semiMinorAxis * semiMinorAxis)) };
	return perimeter + ropeForConstruction;
}

double Ellipse::seeds() const {
	return pi * semiMajorAxis * semiMinorAxis * seedPerSquareMeter;
}

}
