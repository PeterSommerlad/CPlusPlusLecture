#include <iostream>
int main(){
	double sum{};
	while(std::cin){
		double val{};
		std::cin >> val;
		sum += val;
	}
	std::cout << sum << " sum of doubles\n";
}
