#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Shape.h"
#include <string>

namespace Gardening {

struct Circle : Shape {
	static unsigned const requiredPegs;
	static std::string const name;

	explicit Circle(double radius);

	unsigned pegs() const;
	double ropes() const;
	double seeds() const;

private:
	double const radius;
};

}

#endif /* CIRCLE_H_ */
