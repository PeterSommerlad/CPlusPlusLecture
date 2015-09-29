#include <iostream>








int factorial(int n){
	if (n > 1) return n * factorial(n-1);
	return 1;
}
double factorial(double n) {
	double result=1;
	if (n < 15)
		return factorial(int(n));
	while(n > 1) {
		result *= n;
		--n;
	}
	return result;
}
void demoAmbiguity() {
	/*
	factorial(10u); // ambiguous
	factorial(1e1l);// ambiguous
	*/
	std::cout << factorial(3) << "\n";
	std::cout << factorial(1e2) << "\n";
}
