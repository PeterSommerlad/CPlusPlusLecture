#include "long_function.h"
#include <fstream>
#include <string>
#include <iostream>





bool writeNTimesToFile( std::string filename
                      , std::string content
                      , size_t n){
	//open the file
	std::ofstream file { filename, std::ios_base::app };
	// check if it is OK and then write
	if (! file.good()) return false;
	// write content n times
	while (--n>0){
		// write the content on a line
		file << content;
		file << '\n';
	}
	// write another new line and flush it
	file << std::endl;
	return true;
}



void writeNTimesToStream( std::ostream& file
                        , std::string content
                        , size_t n) {
	while (--n > 0) {
		file << content << '\n';
	}
}



bool writeNTimesToFile2( std::string filename
		               , std::string content
		               , size_t n){
	//open the file
	std::ofstream file { filename, std::ios_base::app };
	// check if it is OK and then write
	if (! file.good()) return false;
	writeNTimesToStream(file, content,n );
	file << std::endl;
	return true;
}









bool writeNTimesToStreamIfOk( std::ostream& file
                            , std::string content
                            , size_t n){
	if (! file.good()) return false;
	writeNTimesToStream(file, content,n );
	file << std::endl;
	return true;
}


bool writeNTimesToFile3( std::string filename
                       , std::string content
                       , size_t n){
	std::ofstream file { filename, std::ios_base::app };
	return writeNTimesToStreamIfOk(file,content,n);
}





//int main(){
//	std::cout << writeToFile("hello.txt","hello, world!",10);
//}
