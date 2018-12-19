#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Shape.h"
#include <string>

namespace Gardening {

struct Triangle : Shape {
	static unsigned const requiredPegs;
	static std::string const name;

	Triangle(double sideA, double sideB, double sideC);

	unsigned pegs() const;
	double ropes() const;
	double seeds() const;

private:
	const double sideA;
	const double sideB;
	const double sideC;
	bool checkTriangleInput() const;
	double perimeter() const;
};

}

#endif /* TRIANGLE_H_ */
