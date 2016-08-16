#include <stdexcept>
#include <iostream>
constexpr int fac(int i) {
	if (i > 0)
		return i * fac(i - 1);
	else if (i == 0)
		return 1;
	else
		throw std::invalid_argument{"negative"};
}

int main(){
	char s[fac(6)]; // check compile time execution
	std::cout << "sizeof s = "<< sizeof(s);
	fac(-1); // run-time error
	//constexpr auto val=fac(-2); // compile time error
	//constexpr auto val1=fac(13); // overflow-> compile time error
}



