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

void Person::killMe() {
	// here shared_from_this is possible, not in ctor or dtor
	auto me=shared_from_this();
	if (father) father->killChild(me);
	if (mother) mother->killChild(me);
	for(PersonPtr son:children){
		if (me == son->father) son->father.reset();
		if (me == son->mother) son->mother.reset();
	}
	children.clear();
}
