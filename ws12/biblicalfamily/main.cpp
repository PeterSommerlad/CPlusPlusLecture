#include "Person.h"
#include <iostream>

void addson(std::string name,PersonPtr adam, PersonPtr eva) {
	auto son = Person::makePerson(name);
	eva->addChild(son);
	adam->addChild(son);
}

int main() {
	auto adam=Person::makePerson("Adam");
	adam->print(std::cout);
	auto eva=Person::makePerson("Eva");
	eva->print(std::cout);
	addson("Cain",adam, eva);
	addson("Abel",adam, eva);
	addson("Seth",adam, eva);
	adam->print(std::cout);
	eva->print(std::cout);
	// how to have Cain kill Abel?
}



