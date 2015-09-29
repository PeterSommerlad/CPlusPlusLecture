#include <iostream>
#include <string>







std::string inputName(std::istream &in) {
	std::string name{};
	in >> name;
	return name.size()?name:"anonymous";
}





std::string inputNameWithDefault(std::istream &in
		          , std::string const &def="anonymous") {
	std::string name{};
	in >> name;
	return name.size()?name:def;
}




void inputNameBadExample(){
	auto name=inputNameWithDefault(std::cin,"noname");
	if (name == "noname"){
		return;
	}
	// continue processing
}



int doSomething(int input, int &error_status);

