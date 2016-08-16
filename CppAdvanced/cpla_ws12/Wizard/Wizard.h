#ifndef WIZARD_H_
#define WIZARD_H_
#include <string>
#include <vector>
#include "WizardIngredients.h"

class Wizard { // all magic details public
	std::string name;
	MagicWand  wand;
	std::vector<Spell> books;
	std::vector<Potion> potions;
	std::string searchForSpell(std::string const &wish);
	Potion mixPotion(std::string const &recipe);
	void castSpell(Spell spell);
	void applyPotion(Potion phial);
public:
	Wizard(std::string name="Rincewind"):name{name}, wand{}{}
	std::string doMagic(std::string const &wish);
	void learnSpell(std::string const &newspell);
	void mixAndStorePotion(std::string const &potion);
	std::string getName() const { return name ; }
};

#endif /* WIZARD_H_ */
