// file to demonstrate lifetime issues of variables
#include <iostream>







int & doNeverDoThis_ReturnReferenceToLocalVariable(){
	int number{42};
	return number;
}






void showScopingRules(int i, double d){
	unsigned j{1}; // can not use name i instead of j
	std::cout << i<< "\n";
	{
		char i{'d'}; // shadows parameter i
		// parameter i not accessible but d is
		std::cout << i << " " << d << "\n";
	}
	++i; // that is the parameter no longer shadowed
	for (unsigned i=0;i<j;++i){ // another i
		std::cout << i<< "\n";
	}
	std::cout << i << "\n"; // parameter i again
}
