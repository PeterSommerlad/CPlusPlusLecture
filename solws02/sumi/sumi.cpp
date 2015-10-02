#include <iostream>
int main(){
	int sum{};
	while(std::cin){
		int val{};
		std::cin >> val;
		sum += val;
	}
	std::cout << sum << " sum of integers\n";
}
