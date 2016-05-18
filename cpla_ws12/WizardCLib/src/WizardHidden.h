#ifndef WIZARDHIDDEN_H_
#define WIZARDHIDDEN_H_
#include <string>
#include <vector>
#include "WizardIngredients.h"

namespace unseen{
struct Wizard {
private:
	std::string const name;
	MagicWand  const wand;
	std::vector<Spell> books;
	std::vector<Potion> potions;
	std::string searchForSpell(std::string const &wish);
	Potion mixPotion(std::string const &recipe);
	void castSpell(Spell spell);
	void applyPotion(Potion phial);
public:
	Wizard(std::string name="Rincewind"):name{name}, wand{}{}
	char const * doMagic(std::string const &wish);
	void learnSpell(std::string const &newspell);
	void mixAndStorePotion(std::string const &potion);
	char const * getName() const { return name.c_str() ; }
};
}
#endif /* WIZARDHIDDEN_H_ */
