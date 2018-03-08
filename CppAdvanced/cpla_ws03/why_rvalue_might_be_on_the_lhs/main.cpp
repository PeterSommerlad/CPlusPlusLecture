#include<iostream>
#include<string>

struct S {
	S& operator=(std::string const & s) /*&*/ { // & prohibits calling non-const member functions on temporaries
		std::cout << "got \"" << s << "\" assigned\n";
		return *this;
	}
};

int main(int argc, char **argv) {
	S{} = "new value";
}
