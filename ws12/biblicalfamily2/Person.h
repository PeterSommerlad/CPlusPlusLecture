#ifndef PERSON_H_
#define PERSON_H_
#include <memory>
#include <string>
#include <vector>
#include <iosfwd>
using PersonPtr=std::shared_ptr<class Person>;

class Person {
	std::string name;
	PersonPtr father;
	PersonPtr mother;
	std::vector<PersonPtr> children;
public:
	Person(std::string name,PersonPtr father,PersonPtr mother)
	:name{name},father{father},mother{mother}{}
	void addChild(PersonPtr child){
		children.push_back(child);
	}
	std::string getName() const { return name; }
	PersonPtr findChild(std::string name) const;
	void killChild(PersonPtr child);
	void print(std::ostream &) const;
static PersonPtr makePerson(std::string name,
		                    PersonPtr father={},
		                    PersonPtr mother={}){
	auto res =  std::make_shared<Person>(name,father,mother);
	if (father) father->addChild(res);
	if (mother) mother->addChild(res);
	return res;
}
};

#endif /* PERSON_H_ */
