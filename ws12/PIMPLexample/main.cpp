#include "Wizard.h"

#include <iostream>
int main(){
	Pimpl::Wizard harry{"Potter"};
	std::cout << harry.doMagic("Expecto Patronus!");
}



