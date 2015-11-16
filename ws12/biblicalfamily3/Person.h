#ifndef PERSON_H_
#define PERSON_H_
#include <memory>
#include <string>
#include <vector>
#include <iosfwd>
using PersonPtr=std::shared_ptr<class Person>;

class Person : public std::enable_shared_from_this<Person> {
	std::string name;
	PersonPtr father;
	PersonPtr mother;
	std::vector<PersonPtr> children;
public:
	Person(std::string name,PersonPtr father,PersonPtr mother)
	:name{name},father{father},mother{mother}{
		// can not do shared_from_this here!
		//no if(father) father->addChild(shared_from_this());
	}
	void addChild(PersonPtr child){
		children.push_back(child);
	}
	std::string getName() const { return name; }
	PersonPtr findChild(std::string name) const;
	void killChild(PersonPtr child);
	void killMe();
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
