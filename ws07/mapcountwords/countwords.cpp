#include <map>
#include <iostream>
#include <iterator>
int main(){
	std::map<std::string,size_t> words;
	std::string s;
	while (std::cin >> s)
			++words[s];
	for(auto const &p:words)
		std::cout << p.first << " = "<< p.second << '\n';
}
