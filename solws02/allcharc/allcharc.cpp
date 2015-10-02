#include <iostream>
int main(){
	unsigned count{};
	while(std::cin.get()!=std::istream::traits_type::eof() )
		++count;
	std::cout << count << " characters\n";
}



