#include "Person.h"
#include <ostream>

void Person::print(std::ostream& out) const {
	out << "Person: "<< name << '\n';
	out << "    ";
	for(auto child:children){
		out << child->name << ", ";
	}
	out << '\n';
}
