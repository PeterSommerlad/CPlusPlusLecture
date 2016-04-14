#include <type_traits>
#include <iostream>

template <typename INT>
constexpr auto faci(INT i){
	INT res=1;
	while( i>0)
		res*=i--;
	return res;
}

template <typename INT, INT val>
constexpr auto facic(std::integral_constant<INT,val>){
	return std::integral_constant<INT,faci(val)>{};
}

constexpr auto val=facic(std::integral_constant<int,6>{});

int main(){
	std::cout << val.value;
}


