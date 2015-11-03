#include <set>
#include <iostream>
#include <iterator>
int main(){
	std::set<char> vowels{'a','e','i','o','u','y'};
	std::multiset<char> allvowels;
	char c;
	while (std::cin >> c)
		if (vowels.count(c))
			allvowels.insert(c); // map
	for(char v:vowels){
		std::cout << v << " = "<< allvowels.count(v)<<'\n';
	} // reduce
}
