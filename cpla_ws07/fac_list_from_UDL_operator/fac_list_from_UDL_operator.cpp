#include <utility>
#include <type_traits>

#include <array>

#include <iostream>
#include <iterator>
#include <algorithm>


constexpr unsigned long long ten_to(size_t n){
	size_t res=1;
	while (n-->0) res *=10;
	return res;
}
template <char ...> struct parse_digits;

template <>
struct parse_digits<>
:std::integral_constant<unsigned long long,0>{};

template <char D, char ... DIGITS>
struct parse_digits<D,DIGITS...>
: std::integral_constant<unsigned long long,
(D-'0')*ten_to(sizeof...(DIGITS))+parse_digits<DIGITS...>{}
>{};

static_assert(123==parse_digits<'1','2','3'>{});

template <typename F, typename INT, INT...vals>
constexpr auto transform(std::integer_sequence<INT,vals...>){
	return std::integer_sequence<INT,F{}(vals)...>{};
}

struct faci{
	template <typename INT>
	constexpr auto operator()(INT i){
		INT res=1;
		while (i >1) res *=i--;
		return res;
	}
};

template <typename INT,INT...ints>
constexpr auto to_array(std::integer_sequence<INT,ints...>){
	return std::array<INT,sizeof...(ints)>{ints...};
}

template <char ...DIGITS>
constexpr auto operator"" _fac(){
	return to_array(transform<faci>(
			   std::make_index_sequence<
			       parse_digits<DIGITS...>::value
			   >{}));
}
int main() {
	constexpr auto indices=to_array(std::make_index_sequence<10>{});
	constexpr auto ar=10_fac;
	copy(begin(indices),end(indices),std::ostream_iterator<int>{std::cout,",\t"});
	std::cout << '\n';
	copy(begin(ar),end(ar),std::ostream_iterator<int>{std::cout,",\t"});
}


