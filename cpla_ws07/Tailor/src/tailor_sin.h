#ifndef SRC_TAILOR_SIN_H_
#define SRC_TAILOR_SIN_H_

#include <array>
#include <cmath>
// sin(x) = sum (-1)^n*(x^(2*n+1))/(2n+1)!
// cos(x) = sum (-1)^n*(x^(2*n))/(2n)!
namespace tailor {
template<typename T>
constexpr T pi = T(3.1415926535897932384626433L);
namespace detail{
constexpr long double fak(size_t n) {
	long double res = 1;
	for (size_t i = 2; i <= n; ++i) {
		res *= i;
	}
	return res;
}

template <size_t n>
constexpr long double fakt{n * fakt<n-1>};
template <>
constexpr long double fakt<0>{1};

constexpr auto f20=fakt<20>;

template <typename T, size_t n>
struct ar{
	//constexpr ar():a{{}}{}
	constexpr T const & operator[](size_t i) const { if (i<n)return a[i];else throw 0;}
	constexpr T  & operator[](size_t i)  { if (i<n)return a[i]; throw 0;}
//private:
	T a[n];
};

template <size_t ...nums>
constexpr auto make_faks(std::index_sequence<nums...>){
	return ar<long double, sizeof...(nums)>{{fakt<nums>...}};
}

constexpr auto faks=make_faks(std::make_index_sequence<40>{});

constexpr long double
sin_denominator(long double x, size_t n) {
	long double res{ x }; // 1 + 2n
	for (size_t i = 0; i < n + n; ++i)
		res *= x;// naive, could be log(n), n<20
	return res;
}
constexpr long double cos_denominator(long double x, size_t n) {
	long double res{ 1.0 }; // 2 n
	for (size_t i = 0; i < n + n; ++i) { // naive, could be log(n), n<20
		res *= x;
	}
	return res;
}

template<typename T>
constexpr T two_pi =2.0L*pi<T>;

constexpr
long double adjust_to_two_pi(long double x) {
	while (x > two_pi<long double> ) {
		x -= two_pi<long double>;
	}
	while (x < -two_pi<long double> ) {
		x += two_pi<long double>;
	}
	return x;
}
template <typename T>
constexpr auto abs(T x){ return x<0?-x:x;}

constexpr long double squrt(long double x){
	if (x == 0.l)
		return x;
	long double x0 { x }; // try simple first
	long double x1 { (x0 + x0 / x) / 2 };
	while (abs(x1 - x0) > 1e-12 ) {
		x0 = x1;
		x1 = (x0+ x/x0)/2;
	}
	return x1;
}
static_assert(2==squrt(4.0l),"wurzel4ist2");
static_assert(0.0l==squrt(0.0l)," wurzel0ist0");
static_assert(1.0l==squrt(1.0l)," wurzel1ist1");


} // detail
constexpr long double circle(long double x,long double radius=1.0l){
	// x must be between 0 and 1
	return detail::squrt(radius*radius-x*x);
}
static_assert(0.0l==circle(1.0l),"circle 0");
static_assert(1.0l==circle(0.0l),"circle pi/2");
static_assert(detail::squrt(0.5)==circle(detail::squrt(0.5)),"circle 45 degrees");

template <short deg, short minutes=0, short seconds=0>
constexpr long double
degrees{(deg+minutes/60.0l+seconds/3600.0l)*pi<long double>/180.0l};
static_assert(pi<long double>/2 == degrees<90>,"90 degrees are pi half");

using namespace tailor::detail;

constexpr long double sin(long double x) {
	long double res = 0;
	x = adjust_to_two_pi(x);
	for (size_t n = 0; n <= 16; ++n) {
		long double const summand { sin_denominator(x, n) / faks[(2 * n + 1)] };
		res += n % 2 ? -summand : summand;
	}
	return res;
}
constexpr long double cos(long double x) {
	long double res = 0;
	x = detail::adjust_to_two_pi(x);
	for (size_t n = 0; n <= 17; ++n) {
		long double const summand{detail::cos_denominator(x, n) / detail::faks[(2 * n)]};
		res += n % 2 ? -summand : summand;
	}
	return res;
}

}




#endif /* SRC_TAILOR_SIN_H_ */
