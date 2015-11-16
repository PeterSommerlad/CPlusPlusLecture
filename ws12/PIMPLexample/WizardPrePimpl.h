#ifndef WIZARDPREPIMPL_H_
#define WIZARDPREPIMPL_H_
#include "WizardIngredients.h"
#include <string>
#include <vector>
namespace PrePimpl {

class Wizard { // all magic details public
	std::string name;
	MagicWand  wand;
	std::vector<SpellBook> books;
	std::vector<Potion> potions;
	std::string searchForSpell(std::string wish);
	Potion mixPotion(std::string recipe);
	void castSpell(std::string spell);
	void applyPotion(Potion phial);
public:
	Wizard(std::string name="Rincewind"):name{name}, wand{}{}
	std::string doMagic(std::string wish);
};

} /* namespace PrePimpl */
#endif /* WIZARDPREPIMPL_H_ */
