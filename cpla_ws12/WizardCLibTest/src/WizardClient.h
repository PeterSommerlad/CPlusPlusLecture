#ifndef SRC_WIZARDCLIENT_H_
#define SRC_WIZARDCLIENT_H_
#include "Wizard.h"
#include <stdexcept>
#include <string>
namespace wizard_client {
struct ErrorRAII{
	ErrorRAII(error_t error):opaque{error}{}
	~ErrorRAII(){ if (opaque) error_dispose(opaque);}
	error_t opaque;
};

struct ThrowOnError{
	ThrowOnError()=default;
	~ThrowOnError() noexcept(false){
		if(error.opaque){
			throw std::runtime_error{error_message(error.opaque)};
		}
	}
	operator error_t*(){return &error.opaque;}
private:
	ErrorRAII error{nullptr};
};

struct Wizard{
	Wizard(std::string const &who="Rincewind")
	:wiz{createWizard(who.c_str(),ThrowOnError{})}{}
	~Wizard(){ disposeWizard(wiz);}
	std::string doMagic(std::string const &wish){
		return ::doMagic(wiz,wish.c_str(),ThrowOnError{});
	}
	void learnSpell(std::string const &spell){
		::learnSpell(wiz,spell.c_str());
	}
	void mixAndStorePotion(std::string const &potion){
		::mixAndStorePotion(wiz,potion.c_str());
	}
	char const * getName() const { return wizardName(wiz) ; }

private:
	Wizard(Wizard const &)=delete;
	Wizard& operator=(Wizard const &)=delete;

	wizard wiz;
};
}

#endif /* SRC_WIZARDCLIENT_H_ */
