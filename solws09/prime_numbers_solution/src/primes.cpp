#include "primes.h"

#include <boost/iterator/counting_iterator.hpp>

#include <ostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <functional>

bool is_prime(unsigned long long n) {
	if (n == 2) {
		return true;
	}
	if (n == 0 || n == 1 || n % 2 == 0) {
		return false;
	}
	for (auto divisor = 3ull; divisor * divisor <= n; divisor += 2) {
		if (n % divisor == 0) {
			return false;
		}
	}
	return true;
}

bool is_prime_loopless(unsigned long long n) {
	if (n < 2) {
		return false;
	}
	std::vector<unsigned long long> divisors(n-2); //Infeasible for large n
	std::iota(std::begin(divisors), std::end(divisors), 2);
	return std::none_of(std::begin(divisors), std::end(divisors), [n](auto div) {
		return n % div == 0;
	});
}

bool is_prime_boost(unsigned long long n) {
	using std::placeholders::_1;
	if (n == 2) {
			return true;
	}
	if (n == 0 || n == 1 || n % 2 == 0) {
		return false;
	}
	unsigned long long rootOfN = std::sqrt(n) + 1;
	return std::all_of(
			boost::counting_iterator<unsigned long long>{3},
			boost::counting_iterator<unsigned long long>{rootOfN},
			std::bind(std::modulus<>{}, n, _1));
}



void primes(std::ostream & out, unsigned long long limit) {
	std::vector<unsigned long long> primes(limit);
	std::iota(std::begin(primes), std::end(primes), 1);
	std::copy_if(std::begin(primes), std::end(primes), std::ostream_iterator<unsigned long long>{out, "\n"}, is_prime_loopless);
}