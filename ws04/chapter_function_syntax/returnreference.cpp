#include <iostream>








std::ostream &print(std::ostream &out, int value){
	out << value;
	return out;
}






void usePrint(){
	if (print(std::cout,42)){
		std::cout << " printed OK\n";
	} else {
		std::cerr << "couldn't print on cout\n";
	}
}
