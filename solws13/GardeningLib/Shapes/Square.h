#ifndef SQUARE_H_
#define SQUARE_H_

#include "Shape.h"
#include <string>

namespace Gardening {

struct Square : Shape {
	static unsigned const requiredPegs;
	static unsigned const numberOfSides;
	static std::string const name;

	explicit Square(double side);

	unsigned pegs() const;
	double ropes() const;
	double seeds() const;

private:
	double const side;
};

}

#endif /* SQUARE_H_ */
