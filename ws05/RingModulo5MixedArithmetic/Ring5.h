#ifndef RING5_H_
#define RING5_H_
#include <iosfwd>
#include <boost/operators.hpp>
struct Ring5
: boost::equality_comparable<Ring5> {
    explicit Ring5(unsigned x=0u) : val{ x % 5 } {}
    unsigned value() const { return val; }
    explicit operator unsigned() const { return val; }
    bool operator==(Ring5 const &r) const {
        return val == r.val;
    }
    Ring5 operator+=(Ring5 const &r) {
        val = (val + r.value())%5;
        return *this;
    }
    Ring5 operator+=(unsigned r) {
        val = (val + r)%5;
        return *this;
    }
    Ring5 operator+(Ring5 const&r) const {
        Ring5 res{*this};
        res += r;
        return res;
    }
    friend Ring5 operator+(unsigned l, Ring5 const &r) {
        return Ring5{l+r.val};
    }
    friend Ring5 operator+(Ring5 l, unsigned r) {
        l.val = (l.val + r)%5;
        return l;
    }
    Ring5 operator*=(Ring5 const&r) {
        val = (val * r.value())%5;
        return *this;
    }
    Ring5 operator*=(unsigned r) {
        val = (val * r)%5;
        return *this;
    }
    Ring5 operator*(unsigned r) const {
        Ring5 res{r};
        res.val = (res.val * val)%5;
        return res;
    }
private:
    unsigned val;
};
inline Ring5 operator*(Ring5 l, Ring5 const &r){
     l *= r;
     return l;
}
inline Ring5 operator*(unsigned l, Ring5 const &r) {
    return Ring5{l*r.value()};
}
std::ostream& operator <<(std::ostream& out, const Ring5& r);
#endif /* RING5_H_ */
