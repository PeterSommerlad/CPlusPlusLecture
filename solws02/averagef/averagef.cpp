#include <iostream>
int main(){
	double sum{};
	unsigned count{};
	while(std::cin){
		double val{};
		if (std::cin >> val) ++count;
		sum += val;
	}
	if (count) std::cout << sum/count << " average of floating point numbers\n";
}
