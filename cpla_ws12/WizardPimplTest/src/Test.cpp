#include "Wizard.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void canCreateDefaultWizard() {
	const Wizard magician { };
	ASSERT_EQUAL("Rincewind",magician.getName());
}
void canCreateWizardWithName(){
	const Wizard magician { "Petrosilius Zwackelmann" };
	ASSERT_EQUAL("Petrosilius Zwackelmann",magician.getName());
}

void wizardLearnsSpellAndCanRecall(){
	Wizard magician{};
	magician.learnSpell("Expelliarmus");
	ASSERT_EQUAL("wootsh",magician.doMagic("Expelliarmus"));
}
void wizardMixesPotionAndCanApply(){
	Wizard magician{};
	magician.mixAndStorePotion("Polyjuice Potion");
	ASSERT_EQUAL("zapp",magician.doMagic("Polyjuice Potion"));
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(canCreateDefaultWizard));
	s.push_back(CUTE(canCreateWizardWithName));
	s.push_back(CUTE(wizardLearnsSpellAndCanRecall));
	s.push_back(CUTE(wizardMixesPotionAndCanApply));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



