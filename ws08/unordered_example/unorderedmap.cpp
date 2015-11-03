#include <unordered_map>
#include <iostream>
#include <string>
int main(){
	std::unordered_map<std::string,int> words;
	std::string s;
	while (std::cin >> s)
			++words[s];
	for(auto const &p:words)
		std::cout << p.first << " = "<< p.second << '\n';
}
