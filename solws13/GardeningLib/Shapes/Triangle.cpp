/*
 * Triangle.cpp
 *
 *  Created on: 02.05.2011
 *      Author: tcorbat
 */

#include "Triangle.h"

#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <string>

namespace Gardening {

const unsigned Triangle::requiredPegs = 3;
const std::string Triangle::name = "Triangle";

Triangle::Triangle(double sideA, double sideB, double sideC) :
		Shape { name }, sideA { sideA }, sideB { sideB }, sideC { sideC } {
	if (!checkTriangleInput()) {
		throw std::invalid_argument{"Side lengths do not form a proper triangle."};
	}
}

template<typename T>
inline T max3(T a, T b, T c)
{
    return std::max(a, std::max(b, c));
}

bool Triangle::checkTriangleInput() const {
	if (sideA <= 0.0 || sideB < 0.0 || sideC < 0.0) {
		return false;
	}
	double const longestSide = max3(sideA, sideB, sideC);
	return sideA + sideB + sideC > 2 * longestSide;
}

unsigned Triangle::pegs() const {
	return requiredPegs;
}

double Triangle::ropes() const {
	return perimeter();
}

double Triangle::seeds() const {
	//Heron
	double const semiperimeter { perimeter() / 2 };
	double const area = std::sqrt(semiperimeter * (semiperimeter - sideA) * (semiperimeter - sideB) * (semiperimeter - sideC));
	return area * seedPerSquareMeter;
}

double Triangle::perimeter() const {
	return sideA + sideB + sideC;
}

}
