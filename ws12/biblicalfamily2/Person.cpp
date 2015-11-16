#include "Person.h"
#include <ostream>
#include <algorithm>
#include <functional>

void Person::print(std::ostream& out) const {
	out << "Person: "<< name ;
	out << "   "<< (father?father->getName():"orphan");
	out << "   "<< (mother?mother->getName():"orphan");
	out << "\n    ";
	for(auto const &child:children){
		out << child->name << ", ";
	}
	out << '\n';
}

PersonPtr Person::findChild(std::string theName) const {
	using namespace std::placeholders;
	auto finder=[theName](PersonPtr const &person){
		return person->getName() == theName;
	};
	auto it=find_if(children.begin(),children.end(),finder);
	if (it != children.end()) return *it;
	return nullptr;
}

void Person::killChild(PersonPtr child) {
	if (child){
		children.erase(find(children.begin(),children.end(),child));
		//if (child->father == ) ?
	}
}
