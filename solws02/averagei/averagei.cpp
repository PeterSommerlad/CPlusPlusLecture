#include <iostream>
int main(){
	int sum{};
	unsigned count{};
	while(std::cin){
		int val{};
		if (std::cin >> val) ++count;
		sum += val;
	}
	if (count) std::cout << double(sum)/count << " average of integers\n";
}
