#include <iostream>
#include <string>
int main(){
	unsigned count{};
	std::string s{};
	while(std::cin>>s)++count;
	std::cout << count << " words\n";
}



