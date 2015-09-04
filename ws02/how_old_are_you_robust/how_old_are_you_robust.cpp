#include <iostream>
#include <sstream>
int inputAge(std::istream& in) {
	while (in) {
		std::string line{};
		getline(in, line);
		int age{-1};
		// /*
		std::istringstream is{line};
		if (is >> age)
			return age;
		// */
		// alternative:
		/*
		try{
			age=std::stoi(line);
			return age;
		}
		catch(...){}
		*/
	}
	return -1;
}


int main() {
	std::cout << "Enter your age: " << std::flush;

	std::cout << "\nYou are " << inputAge(std::cin)
			  << " years old\n";
}

