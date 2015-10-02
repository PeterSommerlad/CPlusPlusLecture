#include <iostream>
#include <string>
int main(){
	unsigned count{};
	std::string s{};
	while(getline(std::cin,s))++count;
	std::cout << count << " lines\n";
}







