#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "println.h"
#include <tuple>
#include <type_traits>
//#define SIMPLE_BUT_WRONG
constexpr
auto fizzbuzz_number(std::index_sequence<0>){
	return std::tuple<>{};
}
#if defined(SIMPLE_BUT_WRONG)
constexpr
auto fizzbuzz_number(std::index_sequence<3>){
	return std::make_tuple("Fizz");
}
constexpr
auto fizzbuzz_number(std::index_sequence<5>){
	return std::make_tuple("Buzz");
}
constexpr
auto fizzbuzz_number(std::index_sequence<15>){
	return std::make_tuple("FizzBuzz");
}
template<size_t value>
constexpr
auto fizzbuzz_number(std::index_sequence<value>)
{
	return std::make_tuple(value);
}


#else
template<size_t value>
constexpr auto fizzbuzz_number(std::index_sequence<value>,
		std::enable_if_t<value%3&&value%5,void*> =nullptr)
{
	return std::make_tuple(value);
}
template<size_t value>
constexpr auto fizzbuzz_number(std::index_sequence<value>,
		 std::enable_if_t<value%3==0&&value%5,void*> =nullptr)
{
	return std::make_tuple("Fizz");
}
template<size_t value>
constexpr auto fizzbuzz_number(std::index_sequence<value>,
		std::enable_if_t<value%3&&value%5==0,void*> =nullptr)
{
	return std::make_tuple("Buzz");
}
template<size_t value>
constexpr auto fizzbuzz_number(std::index_sequence<value>,
		typename std::enable_if<value%15==0,void*>::type =nullptr)
{
	return std::make_tuple("FizzBuzz");
}
#endif

template<size_t ...values>
constexpr
auto fizzbuzz(std::index_sequence<values...>);
constexpr
auto fizzbuzz(std::index_sequence<>){
	return std::tuple<>{};
}

template<size_t ...values>
constexpr
auto fizzbuzz(std::index_sequence<values...>)
{
	return tuple_cat(
			fizzbuzz_number(std::index_sequence<values>{})...);
}

// variable template for fizzbuzz

template <size_t n>
constexpr auto fizzbuzz_v=fizzbuzz(std::make_index_sequence<n>{});


// should be decltype(auto) below but CDT parser doesn't understand (yet)

template
<typename F, typename Tuple, size_t... I>
auto apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>){
	return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
}
template <typename F, typename Tuple>
auto apply(F&& f, Tuple&& t) {
	using Indices = std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>;
	return apply_impl(std::forward<F>(f), std::forward<Tuple>(t), Indices{});
}

template <typename ...T>
std::ostream& operator<<(std::ostream &out,std::tuple<T...> const &toprint){
	auto const printer=[&out](auto&&...t){ println(out,t...);};
	apply(printer,toprint);
	return out;
}
void testFizzBuzzNumberOne(){
	ASSERT_EQUAL(std::make_tuple(1),fizzbuzz_number(std::index_sequence<1>()));
}
void testFizzBuzzNumberTwo(){
	ASSERT_EQUAL(std::make_tuple(2),fizzbuzz_number(std::index_sequence<2>()));
}
void testFizzBuzzNumberThree(){
	ASSERT_EQUAL(std::make_tuple("Fizz"),fizzbuzz_number(std::index_sequence<3>()));
}
void testFizzBuzzNumberFive(){
	ASSERT_EQUAL(std::make_tuple("Buzz"),fizzbuzz_number(std::index_sequence<5>()));
}
void testFizzBuzzNumberFifteen(){
	ASSERT_EQUAL(std::make_tuple("FizzBuzz"),fizzbuzz_number(std::index_sequence<15>()));
}

constexpr auto expected=std::make_tuple(
		1,2,"Fizz",4,"Buzz","Fizz",7,8,
		"Fizz","Buzz",11,"Fizz",13,14,"FizzBuzz",16);
constexpr auto result=fizzbuzz(std::make_index_sequence<17>());
static_assert(expected==result, "Fizzbuzz should work at compile time");

static_assert(expected==fizzbuzz_v<17>,"fizzbuzz_v should work");

void testFizzBuzzSequenceUpTo16() {
	auto const expected=std::make_tuple(
			1,2,"Fizz",4,"Buzz","Fizz",7,8,
			"Fizz","Buzz",11,"Fizz",13,14,"FizzBuzz",16);
	auto const result=fizzbuzz(std::make_index_sequence<17>());
#ifndef SIMPLE_BUT_WRONG
	ASSERT_EQUAL(expected,result);
#else
	ASSERTM("can not compare tuples",false);
#endif

}
void testFizzBuzzPrinting(){
	std::ostringstream out{};
	out << fizzbuzz(std::make_index_sequence<17>());
	ASSERT_EQUAL("1, 2, Fizz, 4, Buzz, Fizz, 7, 8, Fizz, Buzz, 11, Fizz, 13, 14, FizzBuzz, 16\n",
			out.str());
}


void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testFizzBuzzNumberOne));
	s.push_back(CUTE(testFizzBuzzNumberTwo));
	s.push_back(CUTE(testFizzBuzzNumberThree));
	s.push_back(CUTE(testFizzBuzzNumberFive));
	s.push_back(CUTE(testFizzBuzzNumberFifteen));
	s.push_back(CUTE(testFizzBuzzSequenceUpTo16));
	s.push_back(CUTE(testFizzBuzzPrinting));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



