#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <sstream>
#include "long_function.h"
#include <fstream>
#include <cstdio>
void demonstrateMoveTiming() {
	std::ostringstream out { };
	writeNTimesToStream(out,"hello",4);
	ASSERT_EQUAL("hello\nhello\nhello\n",out.str());
}
void testWriting3TimesIfOk() {
	std::ostringstream out { };
	bool ok = writeNTimesToStreamIfOk(out,"hello",4);
	ASSERTM("writing succeeded",ok);
	ASSERT_EQUAL("hello\nhello\nhello\n\n",out.str());
}

void testWriting3TimesIfNotOk() {
	std::ostringstream out { };
	out.clear(std::ios_base::badbit);
	bool ok = writeNTimesToStreamIfOk(out,"hello",3);
	ASSERTM("writing should have failed",not ok);
	ASSERT_EQUAL("",out.str());
}



void testWrite2TimesToRealFile(){
	std::string filename{"hello.txt"};
	std::remove(filename.c_str());
	bool ok= writeNTimesToFile3(filename,"hello",3);
	ASSERTM("writing should succeed",ok);
	std::ifstream in{filename};
	ASSERT(in.good());
	std::ostringstream all{};
	all<<in.rdbuf();
	ASSERT_EQUAL("hello\nhello\n\n",all.str());
}
void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(demonstrateMoveTiming));
	s.push_back(CUTE(testWriting3TimesIfOk));
	s.push_back(CUTE(testWriting3TimesIfNotOk));
	s.push_back(CUTE(testWrite2TimesToRealFile));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
	using std::string;
	string s{"no std::"};
	using str=std::string;
	str t{"short alias"};
    runAllTests(argc,argv);
    return 0;
}



