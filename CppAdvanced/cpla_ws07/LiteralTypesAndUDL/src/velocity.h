#ifndef SRC_VELOCITY_H_
#define SRC_VELOCITY_H_

#include <ostream>
struct velocity {
	explicit constexpr velocity(double initial):v{initial}{}
	constexpr velocity& operator+=(velocity vdelta){ v+=vdelta.v; return *this;}
	friend std::ostream&operator<<(std::ostream &out,velocity const &v){
		return out << v.v << " m/s ";
	}
	constexpr bool operator==(velocity const &other) const{return v == other.v;} // bad impl.
private:
	double v;
};

constexpr velocity operator+(velocity v, velocity const &delta) {
	return v += delta;
}

constexpr velocity operator"" _km_h(long double v) { return velocity{double(v)/3.6};}
constexpr velocity operator"" _km_h(unsigned long long v) { return velocity{double(v)/3.6};}
constexpr velocity operator"" _m_s(long double v) { return velocity(v);}
constexpr velocity operator"" _m_s(unsigned long long v) { return velocity(v);}

static_assert(5_km_h == 5.0_km_h,"velocity UDL does not compare equal");
static_assert(3.6_km_h == 1_m_s,"km_h and m_s inconsistent");


#endif /* SRC_VELOCITY_H_ */
