#include "ratio_operators.h"
#include <ratio>
#include <type_traits>
#include <iostream>


template <typename R,  typename = std::enable_if_t<is_ratio<R>{}>>
constexpr long double value_of{static_cast<long double>(R::num)/R::den};

using namespace std;


using third=ratio<1,3>;
using half=ratio<1,2>;

using X=ratio_add<half,third>;

template <typename RATIO, typename =std::enable_if_t<is_ratio<RATIO>{}>>
std::ostream &operator<<(std::ostream &out,RATIO const &r){
	return out << '(' << r.num << '/' << r.den<< ')';

}

int main() {
	std::cout << X{};

	std::cout << ratio<1,2>{}+ratio<1,4>{};
	constexpr ratio<1,3> r;
	constexpr ratio<2,5> q;
	if (r < q) std::cout << r << "is less" << q;
	else std::cout << q << "is less" << r;
	std::cout << "\nvalue_of<third> = "<< value_of<third>;
	using namespace ratio_literals;
	std::cout << "\n3_den = "<< 3_den;

}
