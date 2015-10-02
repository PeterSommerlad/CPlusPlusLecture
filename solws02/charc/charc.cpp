#include <iostream>
int main(){
	unsigned count{};
	char c{};
	while(std::cin>>c)++count;
	std::cout << count << " non-whitespace characters\n";
}



