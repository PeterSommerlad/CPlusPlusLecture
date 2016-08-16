#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <array>

template <size_t n>
constexpr size_t fibo_v{fibo_v<n-1>+fibo_v<n-2>};
template<>
constexpr size_t fibo_v<0u>{0u};
template<>
constexpr size_t fibo_v<1u>{1u};

namespace detail{

template <size_t ...ns>
constexpr auto const fiboa_helper(std::index_sequence<ns...>){
	return std::array<size_t,sizeof...(ns)>{
		fibo_v<ns>...
	};
}

}

template <size_t n>
constexpr auto fiboa(){
	return detail::fiboa_helper(std::make_index_sequence<n>{});
}

template <size_t n>
constexpr auto fiboa_v=fiboa<n>();

namespace fiboa_literals{
namespace detail {
constexpr unsigned long long pow10(std::size_t n){
	unsigned long long res { 1 };
	while (n--){ res *= 10ull;}
	return res;
}
template <typename... C>
constexpr unsigned long long parsenum(C...num){
	return 0;
}
template <typename ...C>
constexpr unsigned long long parsenum(char d,C...n){
	return (d-'0')*pow10(sizeof...(n))+parsenum(n...);
}
}
template <char ...c>
constexpr auto operator"" _fiboa(){
	return fiboa_v<detail::parsenum(c...)>;
}
}

// std::equal is not (yet) constexpr
template <size_t n>
constexpr bool array_equal(std::array<size_t,n> const &l, std::array<size_t,n> const &r){
	for (size_t i=0; i < n; ++i)
		if(l[i]!=r[i]) return false;
	return true;
}

void thisIsATest() {
	using namespace fiboa_literals;
	constexpr std::array<size_t,10> exp{0,1,1,2,3,5,8,13,21,34};
	ASSERT_EQUAL(exp,10_fiboa);
	static_assert(array_equal(exp,10_fiboa),"check compiletime fiboa suffix works");
	constexpr auto const fibo100=100_fiboa;
	static_assert(fibo_v<99> == fibo100[99],"does 100 fibo numbers also work?");
	//static_assert(fibo_v<99> == 100_fiboa[99],"does 100 fibo numbers also work?");// doesn't compile until C++17
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



