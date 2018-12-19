#ifndef ELLIPSE_H_
#define ELLIPSE_H_

#include "Shape.h"
#include <string>

namespace Gardening {

struct Ellipse : Shape {
	static unsigned const requiredPegs;
	static std::string const name;

	Ellipse(double semiMajorAxis, double semiMinorAxis);

	unsigned pegs() const;
	double ropes() const;
	double seeds() const;

private:
	double const semiMajorAxis;
	double const semiMinorAxis;
};

}

#endif /* ELLIPSE_H_ */
