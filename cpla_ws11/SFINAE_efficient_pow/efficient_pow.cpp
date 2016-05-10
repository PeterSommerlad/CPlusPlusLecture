#include <type_traits>
#include <cmath>
#include <iostream>
#include <string>
#include <complex>

template <typename T, typename P>
std::enable_if_t<std::is_integral<P>{} && std::is_arithmetic<T>{}
,T>
pow(T factor,P power){
	T result = 1;
	while (power > 0){ // could be log
		result *=factor;
		--power;
	}
	while(power < 0){
		result /= factor;
		++power;
	}
	return result;
}
template <typename T, typename P>
std::enable_if_t<std::is_floating_point<P>{}&& std::is_arithmetic<T>{}
,decltype(std::pow(T{},P{}))>
pow(T factor,P power){
	return std::pow(factor,std::common_type_t<T,P>(power));
}
std::string pow(...){ return "undefined";}
int main() {
	using namespace std::literals;
	std::cout << std::scientific;
	std::cout << pow(2,16u) << std::endl;
	std::cout << pow(2.0,4) << std::endl;
	std::cout << pow(2.0,-2) << std::endl;
	std::cout << pow(2.0,0.5) << std::endl;
	std::cout << pow(1i,2) << std::endl;
	std::cout << pow(1i,2.0) << std::endl;
	std::cout << pow("12"s,3);
}

