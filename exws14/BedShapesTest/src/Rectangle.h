/*
 * Rectangle.h
 *
 *  Created on: Apr 30, 2010
 *      Author: sop
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Square.h"
#include <iosfwd>

class Rectangle: public Shape {
	double length;
	double width;
public:
	Rectangle(double len, double wid);
	Rectangle(std::istream &);
	unsigned int pegs() const;
	double rope() const;
	double seeds() const;
	std::string name() const;
};

#endif /* RECTANGLE_H_ */
