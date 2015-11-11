#include "Switch.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void testoutputOfSwitch() {
	Switch s{};
	std::ostringstream out{};
	out << s;
	s.PushButton();
	out << s;
	s.PushButton();
	out << s;
	s.PushButton();
	out << s;
	s.PushButton();
	out << s;
	ASSERT_EQUAL("offonblinkoffon",out.str());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testoutputOfSwitch));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



