#include <set>
#include <iostream>
void filtervowels(std::istream &in, std::ostream &out){
	std::set<char> const vowels{'a','e','o','u','i','y'};
	char c{};
	while (in>>c)
		if (! vowels.count(c))
			out << c;
}
int main(){
	filtervowels(std::cin,std::cout);
}
