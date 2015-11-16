#include "SackSpecializations.h"
#include "Sack.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void testInstantiationPossibilities() {
	Sack<char> scrabble{};
	//Sack<int*> shouldntcompile{};
	Sack<char const *> sackforstringliterals{};
	ASSERTM("only compilation tested",true);
}

void testSackWithPointersShouldntCompile(){
	//Sack<int *> shouldNotCompile;
	Sack<char const *> shouldkeepStrings;
}





void testmakeSackInt(){
	auto sack=makeSack({1,2,3,4,5,6});
	ASSERT_EQUAL(6,sack.size());
}
void testmakeSackCharPtr(){
	auto sack=makeSack({"Hello",",","World","!"});
	ASSERT_EQUAL(4,sack.size());
	ASSERT_EQUAL("!",sack.getOut());
	ASSERT_EQUAL("World",sack.getOut());
	ASSERT_EQUAL(",",sack.getOut());
	ASSERT_EQUAL("Hello",sack.getOut());
	ASSERT_THROWS(sack.getOut(),std::logic_error);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testInstantiationPossibilities));
	s.push_back(CUTE(testmakeSackInt));
	s.push_back(CUTE(testmakeSackCharPtr));
	s.push_back(CUTE(testSackWithPointersShouldntCompile));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



