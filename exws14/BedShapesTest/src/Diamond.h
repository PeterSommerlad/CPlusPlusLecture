#ifndef DIAMOND_H_
#define DIAMOND_H_

#include "Shape.h"
#include <iosfwd>
class Diamond: public Shape {
	double a,b;
	double angleInRadian;
public:
	Diamond(double side1, double side2, double angleInDegrees);
	Diamond(std::istream&);
	unsigned int pegs() const;
	double rope() const;
	double seeds() const;
	std::string name() const;
};

#endif /* DIAMOND_H_ */
