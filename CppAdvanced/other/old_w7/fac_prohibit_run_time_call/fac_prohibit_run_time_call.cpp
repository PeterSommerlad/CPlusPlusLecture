#include <iostream>
constexpr int fac(const int i) {
extern char const * const fac_should_not_be_called_at_run_time; // undefined symbol
	if (i > 0)
		return i * fac(i - 1);
	else if (i == 0)
		return 1;
	else
		throw fac_should_not_be_called_at_run_time; // will raise linker error
}


int main(){
	constexpr auto val=fac(3);
	const char s[fac(6)] { }; // check compile time execution
	std::cout << "sizeof s = "<< sizeof(s);
//	fac(-1); // will raise linker error about undefined symbol
}



