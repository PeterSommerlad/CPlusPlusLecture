#include <utility>
#include <iostream>

struct S {
	S() {
		std::cout << "creating S\n";
	}

	S& operator=(S const &) {
		std::cout << "copy-assigning S\n";
		return *this;
	}

	S& operator=(S&&) {
		std::cout << "move-assigning S\n";
		return *this;
	}
};


int main(int argc, char **argv) {
	std::cout << "\t --- S s1{}, s2{}, s3{} ---\n";
	S s1{}, s2{}, s3{};

	std::cout << "\t --- s1 = s2  (copy!)---\n";
	s1 = s2;

	std::cout << "\t --- s1 = std::move(s3) ---\n";
	s1 = std::move(s3);

	std::cout << "\t --- s3 = S{} (move!) ---\n";
	s3 = S{};

//	s1 = std::move(s1); //Potentially dangerous!
}

