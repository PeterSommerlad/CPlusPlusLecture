#include <iostream>
#include <sstream>
#include <limits>
int inputAge(std::istream& in) {
	while (in.good()) {
		int age{-1};
		if (in>>age)
			return age;
		in.clear(); // remove fail flag
		in.ignore(); // ignore invalid character
		//in.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // whole line
	}
	return -1;
}


int main() {
	std::cout << "Enter your age (invalid ignored): " << std::flush;

	std::cout << "\nYou are " << inputAge(std::cin)
			  << " years old\n";
}

