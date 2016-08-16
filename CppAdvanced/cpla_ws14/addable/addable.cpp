#include <iostream>
#include <numeric>
#include <vector>
#include "addable_sum.h"

/*auto add2(Addable a, Addable b){
	return a+b;
}*/ // internal compiler error
int main(){
	std::vector<int> v(20);
	iota(v.begin(),v.end(),1);
	std::cout << sum(v.begin(),v.end(),0) << '\n';
	std::cout << add(5,37.0) << '\n';
	std::cout << add1(5,37) << '\n';
}
