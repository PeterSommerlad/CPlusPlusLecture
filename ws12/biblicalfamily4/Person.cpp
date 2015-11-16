#include "Person.h"
#include <iostream>
#include <algorithm>
#include <functional>

void Person::print(std::ostream& out) const {
	out << "Person: "<< name ;
	auto realfather=father.lock();
	out << "   "<< (realfather?realfather->getName():"orphan");
	auto realmother=mother.lock();
	out << "   "<< (realmother?realmother->getName():"orphan");
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

PersonPtr Person::myLock() {
	try {
		auto me=shared_from_this(); // throws when called from dtor!
		return me;
	}catch(std::bad_weak_ptr const &ex){}
	std::cerr << "++++already dead? " << name<< '\n';
	return PersonPtr{}; // already dead
}

void Person::killMe() {
	// here shared_from_this is possible
	auto me=myLock();
	if (me == nullptr) return; // already dead
	auto realfather=father.lock();
	if (realfather) realfather->killChild(me);
	auto realmother=mother.lock();
	if (realmother) realmother->killChild(me);
	children.clear();
}

Person::~Person() {
	std::cerr << "killing me: "<< name << '\n';
	//killMe(); // can not call shared_from_this() in dtor!
}

