#ifndef FIELD5_H_
#define FIELD5_H_
#include <iosfwd>
#include <boost/operators.hpp>

struct Field5 {
	explicit constexpr Field5(unsigned x = 0u) :
			val { x % 5 } {
	}
	constexpr unsigned value() const {
		return val;
	}
	constexpr operator unsigned() const {
		return val;
	}
	constexpr bool operator==(Field5 const &r) const {
		return val == r.val;
	}
	constexpr bool operator!=(Field5 const &r) const {
		return !(*this == r);
	}
	constexpr Field5& operator+=(Field5 const &r) {
		val = (val + r.value()) % 5;
		return *this;
	}
	constexpr Field5& operator*=(Field5 const&r) {
		val = (val * r.value()) % 5;
		return *this;
	}
	constexpr Field5 operator+(Field5 const &r) const {
		return Field5 { val + r.val };
	}
	constexpr Field5 operator*(Field5 const &r) const {
		return Field5 { val * r.val };
	}
	constexpr Field5& operator-=(Field5 const &r){
		val = (5 + val-r.value())%5;
		return *this;
	}
	constexpr Field5& operator/=(Field5 const &r){
		return *this *= r.inverse();
	}
private:
	Field5 inverse() const{
		if (val==2) return Field5{3};
		if (val==3) return Field5{2};
		return *this; // not exaclty right for 0
	}
	unsigned val;
};
constexpr Field5 operator-(Field5 l, Field5 const &r){
	l -= r;
	return l;
}
constexpr Field5 operator/(Field5 l, Field5 const &r){
	l /= r;
	return l;
}

std::ostream& operator <<(std::ostream& out,  Field5 const& r);

#endif /* FIELD5_H_ */
