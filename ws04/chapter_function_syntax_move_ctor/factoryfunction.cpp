#include <fstream>
#include <iostream>







std::ofstream fileFactory(std::string filename){
	std::ofstream theFile{filename};
	return theFile;
}






void writeToFile(std::ofstream file){
	file << "hello, world\n";
}





int main(){
	std::ofstream out=fileFactory("hello.txt");
	out << "hello\n";
	writeToFile(std::move(out));
	// cannot use out here anymore
	if (out << "more?"){
		std::cout << "oops out should be empty now\n";
	}
}


