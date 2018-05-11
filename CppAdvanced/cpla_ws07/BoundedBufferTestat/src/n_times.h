#ifndef N_TIMES_H_
#define N_TIMES_H_


namespace cpp_advanced {

namespace times_literal {

struct Executer {
	template<typename T>
	void operator()(T const & action) const {
		for (auto i = 0u; i < times; i++) {
			action();
		}
	}
	unsigned long long const times;
};

constexpr auto operator"" _times(unsigned long long n) {
	return Executer{n};
//  GCC Bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70979
//	return [n](auto f) {
//		for (auto i = 0u; i < n; i++) {
//			f();
//		}
//	};
}

}

}

#endif /* N_TIMES_H_ */
