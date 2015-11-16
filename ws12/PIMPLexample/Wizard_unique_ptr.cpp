#include "Wizard_unique_ptr.h"
#include "WizardIngredients.h"
#include <vector>
namespace PimplUnique {
class WizardImpl { // all magic details public
	std::string name;
	MagicWand  wand;
	std::vector<SpellBook> books;
	std::vector<Potion> potions;
	std::string searchForSpell(std::string wish){
		return "abracadabra";
	}
	Potion mixPotion(std::string recipe) {
		return Potion{};
	}
	void castSpell(std::string spell){}
	void applyPotion(Potion phial){}
public:
	WizardImpl(std::string name):name{name}, wand{}{}
	std::string doMagic(std::string wish){
		auto spell=searchForSpell(wish);
		if (! spell.empty()){
			castSpell(spell);
			return "wootsh";
		}
		auto potion=mixPotion(wish);
		applyPotion(potion);
		return "zapp";
	}
};

Wizard::Wizard(std::string name):pImpl{std::make_unique<WizardImpl>(name)} {
}
Wizard::~Wizard() {} // must define it after WizardImpl is known for unique_ptr PIMPL

std::string Wizard::doMagic(std::string wish) {
	return pImpl->doMagic(wish);
}


} /* namespace PimplUnique */
