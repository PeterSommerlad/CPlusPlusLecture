#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

auto multby=[x=1](auto y){ return x*y; };

void testvariadiclambdawithint() {
	ASSERT_EQUAL(7,multby(7));
}
void testvariadiclambdawithdouble(){
	ASSERT_EQUAL(3.14,multby(3.14));
}



void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testvariadiclambdawithint));
	s.push_back(CUTE(testvariadiclambdawithdouble));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



