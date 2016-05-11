#ifndef TIMES_LITERAL_HPP_
#define TIMES_LITERAL_HPP_

namespace times {
namespace literal {

constexpr auto operator"" _times(unsigned long long n) {
	return [n](auto f){
		for (auto i = 0u; i < n; i++) {
			f();
		}
	};
}

}
}



#endif /* TIMES_LITERAL_HPP_ */
