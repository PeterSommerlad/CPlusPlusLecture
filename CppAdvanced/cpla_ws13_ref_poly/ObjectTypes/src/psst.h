#ifndef SRC_PSST_H_
#define SRC_PSST_H_

#include <type_traits>
#include <ostream>
namespace Psst{


template<typename B, template<typename...>class T>
struct bind2{
	template<typename A, typename ...C>
	using apply=T<A,B,C...>;
};
template<typename A, template<typename...>class T>
struct bind1{
	template<typename ...B>
	using apply=T<A,B...>;
};

template <typename U, template <typename ...> class ...BS>
struct ops:BS<U>...{};


template <typename V, typename TAG>
struct strong { // can not merge ops here, because of initializers required for bases depending on incomplete type
	static_assert(std::is_object_v<V>,"must keep real values");
	V val;
};



template <typename U>
struct is_strong{
	template<typename T>
	static char test(decltype(T::val)*);
	template<typename T>
	static long long test(...);
	static inline constexpr bool value=sizeof(test<U>(nullptr))==sizeof(char);
};

template<typename U>
constexpr inline  bool is_strong_v=is_strong<U>::value;


static_assert(!is_strong_v<int>,"int is no unit");
namespace _____testing_____{
struct bla:strong<int,bla>,ops<bla>{};
static_assert(is_strong_v<bla>,"bla is a unit");
}

// ops templates

template <typename U>
struct Inc{
	friend constexpr auto operator++(U &rv) noexcept {
		return ++rv.val;
	}
	friend constexpr auto operator++(U &rv,int) noexcept {
		auto res=rv;
		++rv;
		return res;
	}
};


template <typename U>
struct Eq{
	friend constexpr bool
	operator==(U const &l, U const& r) noexcept {
		static_assert(is_strong_v<U>,"can only be applied to units");
		return l.val == r.val;
	}
	friend constexpr bool
	operator!=(U const &l, U const& r) noexcept {
		return !(l==r);
	}
};
template <typename U, typename V>
struct EqWithImpl{
	friend constexpr bool
	operator==(U const &l, V const& r) noexcept {
		static_assert(is_strong_v<U>,"can only be applied to units");
		static_assert(!std::is_same_v<U,V>,"can not be applied to identical types");
		if constexpr(is_strong_v<V>)
			return l.val == r.val;
		else
			return l.val == r;
	}
	friend constexpr bool
	operator==(V const &l, U const& r) noexcept {
		return r == l;
	}
	friend constexpr bool
	operator!=(U const &l, V const& r) noexcept {
		return !(l==r);
	}
	friend constexpr bool
	operator!=(V const &l, U const& r) noexcept {
		return !(r==l);
	}
};

template <typename W>
using EqWith=bind2<W,EqWithImpl>;

template <typename U>
struct Cmp{
	friend constexpr bool
	operator<(U const &l, U const& r) noexcept {
		static_assert(is_strong_v<U>,"can only be applied to units");
		return l.val < r.val;
	}
	friend constexpr bool
	operator>(U const &l, U const& r) noexcept {
		return r < l;
	}
	friend constexpr bool
	operator<=(U const &l, U const& r) noexcept {
		return !(r < l);
	}
	friend constexpr bool
	operator>=(U const &l, U const& r) noexcept {
		return !(l < r);
	}
};
template <typename U, typename V>
struct CmpWithImpl{
	friend constexpr bool
	operator<(U const &l, V const& r) noexcept {
		static_assert(is_strong_v<U>,"can only be applied to units");
		static_assert(!std::is_same_v<U,V>,"can not be applied to identical types");
		if constexpr(is_strong_v<V>)
			return l.val < r.val;
		else
			return l.val < r;
	}
	friend constexpr bool
	operator<(V const &l, U const& r) noexcept {
		static_assert(is_strong_v<U>,"can only be applied to units");
		static_assert(!std::is_same_v<U,V>,"can not be applied to identical types");
		if constexpr(is_strong_v<V>)
			return l.val < r.val;
		else
			return l < r.val;
	}
	friend constexpr bool
	operator>(U const &l, V const& r) noexcept {
		return r > l;
	}
	friend constexpr bool
	operator>(V const &l, U const& r) noexcept {
		return r > l;
	}
	friend constexpr bool
	operator<=(U const &l, V const& r) noexcept {
		return !(r > l);
	}
	friend constexpr bool
	operator<=(V const &l, U const& r) noexcept {
		return !(r > l);
	}
	friend constexpr bool
	operator>=(U const &l, V const& r) noexcept {
		return !(l < r);
	}
	friend constexpr bool
	operator>=(V const &l, U const& r) noexcept {
		return !(l < r);
	}
};
template <typename W>
using CmpWith=bind2<W,CmpWithImpl>;


template <typename U>
struct Add {
	friend constexpr U&
	operator+=(U& l, U const &r) noexcept {
		l.val += r.val;
		return l;
	}
	friend constexpr U
	operator+(U l, U const &r) noexcept {
		return l+=r;
	}
};
//todo other useful arithmetic

template <typename U>
struct Out {
	friend std::ostream&
	operator<<(std::ostream &l, U const &r) {
		return l << r.val;
	}
};
}


#endif /* SRC_PSST_H_ */
