#ifndef WIZARD_H_
#define WIZARD_H_
#include <memory>
#include <string>
namespace PimplUnique {

class Wizard {
	std::unique_ptr<class WizardImpl> pImpl;
public:
	Wizard(std::string name);
	~Wizard(); // must declare dtor
	std::string doMagic(std::string wish);
};

} /* namespace PimplUnique */
#endif /* WIZARD_H_ */
