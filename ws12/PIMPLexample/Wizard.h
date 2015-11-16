#ifndef WIZARD_H_
#define WIZARD_H_
#include <memory>
#include <string>
namespace Pimpl {

class Wizard {
	std::shared_ptr<class WizardImpl> pImpl;
public:
	Wizard(std::string name);
	std::string doMagic(std::string wish);
};

} /* namespace Pimpl */
#endif /* WIZARD_H_ */
