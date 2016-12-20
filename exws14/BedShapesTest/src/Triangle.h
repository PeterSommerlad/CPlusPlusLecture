#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Shape.h"
#include <iosfwd>
class Triangle: public Shape {
	double a,b,c; // represent 3 sides
public:
	Triangle(double side1,double side2, double side3);
	Triangle(std::istream &in);
	unsigned int pegs() const;
	double rope() const;
	double seeds() const;
	std::string name() const;
};

#endif /* TRIANGLE_H_ */
