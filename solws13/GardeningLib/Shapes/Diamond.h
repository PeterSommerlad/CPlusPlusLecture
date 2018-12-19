#ifndef DIAMOND_H_
#define DIAMOND_H_

#include "Shape.h"
#include <string>

namespace Gardening {

struct Diamond: Shape {
	static unsigned const requiredPegs;
	static unsigned const numberOfSides;
	static std::string const name;

	Diamond(double sideLength, double angleDegrees);

	unsigned pegs() const;
	double ropes() const;
	double seeds() const;

private:
	double const sideLength;
	double const angle;

	static double convertToRad(double degrees);
};

}

#endif /* DIAMOND_H_ */
