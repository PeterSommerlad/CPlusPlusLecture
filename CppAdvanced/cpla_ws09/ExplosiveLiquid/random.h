#ifndef RANDOM_H_
#define RANDOM_H_


#include <random>

template<unsigned Seed = 4711u, typename RandomDeviceType = std::default_random_engine>
struct PercentageRandomProvider {

	auto operator()() const {
		std::uniform_int_distribution<unsigned> uniform_dist(0, 100);
		return uniform_dist(rng);
	}
private:
	mutable RandomDeviceType rng{};
};



#endif /* RANDOM_H_ */
