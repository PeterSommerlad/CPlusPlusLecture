#include "Shape.h"

#include <cmath>
#include <ostream>
#include <string>

using namespace Gardening;

double const Shape::seedPerSquareMeter { 0.1 };
double const Shape::pi { std::atan(1) * 4 };

Shape::Shape(std::string const & name)
	: name(name){
}

void Shape::print(std::ostream & out) const {
	out << name << " " << pegs() << " " << ropes() << " " << seeds();
}
