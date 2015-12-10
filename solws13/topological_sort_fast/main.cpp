#include "semester_topological.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char * argv[]){
	if (argc>1){
		std::ifstream input{argv[1]};
		print_semester_topological(input,std::cout);
	} else {
		using namespace std::string_literals;
		std::istringstream input {
		R"(
		DB1 OO
		DB2 DB1
		Math
		OO
		AD1 OO
		CPI OO Math
		Thesis DB2 SE2 UI2
		SE1 AD1 CPI DB1
		SE2 DB1 SE1 UI1
		UI1 AD1
		UI2 UI1
		)"s
		};
		print_semester_topological(input,std::cout);
	}
}



