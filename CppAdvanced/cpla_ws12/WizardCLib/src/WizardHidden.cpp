#include "WizardHidden.h"

#include "WizardIngredients.h"
#include <algorithm>
#include <stdexcept>

namespace unseen {

std::string Wizard::searchForSpell(std::string const &wish) {
	auto const spell = find(begin(books), end(books), wish);
	return spell!=end(books)?*spell:"";
}


Potion Wizard::mixPotion(std::string const &recipe) {
	auto const potion = find(begin(potions), end(potions), recipe);
	return potion!=end(potions)?*potion:"";
}

void Wizard::castSpell(std::string spell) {
}

void Wizard::applyPotion(Potion phial) {
}

char const * Wizard::doMagic(std::string const &wish) {
	auto spell=searchForSpell(wish);
	if (! spell.empty()){
		castSpell(spell);
		return "wootsh";
	}
	auto potion=mixPotion(wish);
	if (!potion.empty()){
		applyPotion(potion);
		return "zapp";
	}
	throw std::logic_error{"magic failed"};
}

void Wizard::learnSpell(const std::string& newspell) {
	this->books.push_back(newspell);
}

void Wizard::mixAndStorePotion(const std::string& potion) {
	this->potions.push_back(potion);
}
}
