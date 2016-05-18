#ifndef WIZARD_H_
#define WIZARD_H_
#include <string>
#include <memory>
class Wizard { // all magic details hidden
	std::unique_ptr<class WizardImpl> const pimpl;

public:
	Wizard(std::string name="Rincewind");
	~Wizard(); // must declare and define in .cpp
	std::string doMagic(std::string const &wish);
	void learnSpell(std::string const &newspell);
	void mixAndStorePotion(std::string const &potion);
	std::string getName() const;
};

#endif /* WIZARD_H_ */
