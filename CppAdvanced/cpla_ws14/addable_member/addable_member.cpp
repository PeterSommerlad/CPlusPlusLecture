#include <iostream>
#include <numeric>
#include <vector>
#include "addable_sum.h"

template <typename T>
struct Vec : std::vector<T> {
using std::vector<T>::vector;
auto sum() const ->T requires Addable<T>()  {
	T res{};
	for(auto x:*this){ res = res + x ; }
	return res;
}
};
int main(){
	Vec<int> v(20);
	std::iota(v.begin(),v.end(),1);
	std::cout << sum(v.begin(),v.end(),0) << '\n';
	std::cout << add(5,37.0) << '\n';
	std::cout << v.sum() << '\n';	
}
