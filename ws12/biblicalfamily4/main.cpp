#include "Person.h"
#include <iostream>

void addson(std::string name,PersonPtr adam, PersonPtr eva) {
	auto son = Person::makePerson(name,adam,eva);
}


int main() {
	auto adam=Person::makePerson("Adam");
	adam->print(std::cout);
	auto eve=Person::makePerson("Eve");
	eve->print(std::cout);
	addson("Cain",adam, eve);
	addson("Abel",adam, eve);
	addson("Seth",adam, eve);
	adam->print(std::cout);
	eve->print(std::cout);
	// Cain kills Abel: need to remove from parents
	{
		auto abel=eve->findChild("Abel");
		eve->killChild(abel);
		adam->killChild(abel);
		abel->print(std::cout);
	}
	eve->print(std::cout);
	// kill Adam by forgetting last reference
	{
		std::cout << "killing Adam:\n";
		adam->print(std::cout);
		adam.reset();
	}
	eve->print(std::cout);
	auto cain=eve->findChild("Cain");
	if (cain) cain->print(std::cout);
	eve.reset();
	if (cain) cain->print(std::cout);
}
