#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Shape.h"
#include <string>

namespace Gardening {

struct Rectangle : Shape {
	static unsigned const requiredPegs;
	static std::string const name;

	Rectangle(double sideA, double sideB);

	unsigned pegs() const;
	double ropes() const;
	double seeds() const;

private:
	double const sideA;
	double const sideB;
};

}

#endif /* RECTANGLE_H_ */
