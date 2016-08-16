#include <iostream>
#include <numeric>
#include <vector>
#include "addable_sum.h"

struct X{};

int main(){
	std::vector<int> v(20);
	iota(v.begin(),v.end(),1);
	std::cout << sum(v.begin(),v.end(),X{}) << '\n';
	std::cout << add("hallo\n",2);
	std::cout << add(2,"hallo\n");
}
