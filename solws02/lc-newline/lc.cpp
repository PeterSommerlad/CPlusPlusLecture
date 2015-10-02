#include <iostream>
int main(){
	unsigned count{};
	while(std::cin)
		if (std::cin.get()=='\n')
			++count;
	std::cout << count << " lines\n";
}
