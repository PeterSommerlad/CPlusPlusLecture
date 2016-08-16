#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

namespace velocity {

struct speed {
	constexpr
	explicit
	speed(double kmh) :
			kmh { kmh } {}
	double const kmh;
};

}

#endif /* VELOCITY_HPP_ */
