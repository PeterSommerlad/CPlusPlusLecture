#ifndef SQUARE_H_
#define SQUARE_H_

#include "Shape.h"
#include <iosfwd>
class Square: public Shape {
	double length;
public:
	Square(double len);
	Square(std::istream&);
	unsigned int pegs() const;
	double rope() const;
	double seeds() const;
	std::string name() const;
};

#endif /* SQUARE_H_ */
