/*
 * WizardPrePimpl.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: hsr
 */

#include "WizardPrePimpl.h"

namespace PrePimpl {


std::string Wizard::searchForSpell(std::string wish) {
	return "";
}

Potion Wizard::mixPotion(std::string recipe) {
	return Potion{};
}

void Wizard::castSpell(std::string spell) {
}

void Wizard::applyPotion(Potion phial) {
}

std::string Wizard::doMagic(std::string wish) {
	auto spell=searchForSpell(wish);
	if (! spell.empty()){
		castSpell(spell);
		return "wootsh";
	}
	auto potion=mixPotion(wish);
	applyPotion(potion);
	return "zapp";
}
} /* namespace PrePimpl */
