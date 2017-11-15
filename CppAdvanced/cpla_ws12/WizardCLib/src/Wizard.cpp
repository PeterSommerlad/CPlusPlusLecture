#include "../Wizard.h"
#include "WizardHidden.h"
#include "WizardIngredients.h"
#include <cassert>
#include <stdexcept>

extern "C"{
struct Error {
    std::string message;
};

WIZARD_EXPORT_DLL
const char* error_message(error_type error)
{
    return error->message.c_str();
}

WIZARD_EXPORT_DLL
void error_dispose(error_type error)
{
    delete error;
}
}

template<typename Fn>
bool translateExceptions(error_type* out_error, Fn&& fn)
{
    try {
        fn();
    } catch (const std::exception& e) {
        *out_error = new Error{e.what()};
        return false;
    } catch (...) {
        *out_error = new Error{"Unknown internal error"};
        return false;
    }
    return true;
}

extern "C" {
struct Wizard { // C linkage trampolin
	Wizard(char const *name)
	:wiz{name}{}
	unseen::Wizard wiz;
};


WIZARD_EXPORT_DLL
wizard createWizard(const char* name, error_type *out_error) {
	wizard result=nullptr;
	translateExceptions(out_error,[&]{
		result = new Wizard{name};
	});
	return result;
}

WIZARD_EXPORT_DLL
void disposeWizard(wizard const toDispose) {
	delete toDispose;
}

WIZARD_EXPORT_DLL
char const* doMagic(wizard w, char const * const wish, error_type *out_error) {
	// will return static string!
	char const *result="";
	translateExceptions(out_error,[&]{
		if (!w) throw std::logic_error{"null wizard"};
		result = w->wiz.doMagic(wish);
	});
	return result;
}

WIZARD_EXPORT_DLL
void learnSpell(wizard w, char const * const spell) {
	assert(w);
	w->wiz.learnSpell(spell);
}

WIZARD_EXPORT_DLL
void mixAndStorePotion(wizard w, char const* const potion) {
	assert(w);
	w->wiz.mixAndStorePotion(potion);
}

WIZARD_EXPORT_DLL
char const* wizardName(cwizard const w) {
	assert(w);
	return w->wiz.getName();
}
}
