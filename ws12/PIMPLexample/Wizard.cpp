#include "Wizard.h"
#include "WizardIngredients.h"
#include <vector>
namespace Pimpl {
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

Wizard::Wizard(std::string name):pImpl{std::make_shared<WizardImpl>(name)} {
}

std::string Pimpl::Wizard::doMagic(std::string wish) {
	return pImpl->doMagic(wish);
}


} /* namespace Pimpl */
