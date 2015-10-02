#ifndef RING5_H_
#define RING5_H_
#include <iosfwd>
#include <boost/operators.hpp>





struct Ring5 {
    explicit constexpr
    Ring5(unsigned x=0u) : val{ x % 5 } {}
    constexpr unsigned value() const { return val; }
    constexpr operator unsigned() const { return val; }
    constexpr bool operator==(Ring5 const &r) const {
        return val == r.val;
    }
    constexpr bool operator!=(Ring5 const &r) const {
        return !(*this == r);
    }
    Ring5 operator+=(Ring5 const &r) {
        val = (val + r.value())%5;
        return *this;
    }
    Ring5 operator*=(Ring5 const&r) {
        val = (val * r.value())%5;
        return *this;
    }
    constexpr Ring5 operator+(Ring5 const &r) const {
        return Ring5{val+r.val};
    }
    constexpr Ring5 operator*(Ring5 const &r) const {
        return Ring5{val*r.val};
    }
private:
    unsigned val;
};


namespace R5{
constexpr Ring5
operator"" _R5(unsigned long long v) {
    return Ring5{static_cast<unsigned>(v%5)};
}
}
std::ostream& operator <<(std::ostream& out, const Ring5& r);

#endif /* RING5_H_ */
