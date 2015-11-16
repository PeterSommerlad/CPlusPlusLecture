#ifndef PERSON_H_
#define PERSON_H_
#include <memory>
#include <string>
#include <vector>
#include <iosfwd>
using PersonPtr=std::shared_ptr<class Person>;

class Person {
	std::string name;
	std::vector<PersonPtr> children;
public:
	Person(std::string name):name{name}{}
	void addChild(PersonPtr child){
		children.push_back(child);
	}
	void print(std::ostream &) const;
static PersonPtr makePerson(std::string name){
	return std::make_shared<Person>(name);
}
};

#endif /* PERSON_H_ */
