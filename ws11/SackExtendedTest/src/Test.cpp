#include "Sack.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <deque>
#include <set>
#include <list>



void creationAlsoAllowsTwoInts() {
	Sack<unsigned> asack { 10, 3 };
	ASSERT_EQUAL(10, asack.size());
	ASSERT_EQUAL(3, asack.getOut());
}
void creationAlsoAllowsTwoInts2(){
	Sack<unsigned> asack(10, 3);
	ASSERT_EQUAL(10, asack.size());
	ASSERT_EQUAL(3, asack.getOut());
}



void defaultConstructorStillWorks() {
	Sack<char> defaultctorstillworks { };
	ASSERT_EQUAL(0, defaultctorstillworks.size());
}

void demoInheritingClassTemplateNameResolutionProblem() {
	std::vector<int> v{3,1,4,1,5,9,2,6};
	Sack<int> asack{v.begin(),v.end()};
	ASSERT_EQUAL(v.size(),asack.size());
}

Sack<int> sackForTest() {
	Sack<int> asack;
	asack.putInto(3);
	asack.putInto(2);
	asack.putInto(1);
	return asack;
}

void extractAVectorFromSack() {
	Sack<int> asack = sackForTest();
	auto v=static_cast<std::vector<unsigned>>(asack);
	ASSERT_EQUAL(asack.size(),v.size());
	while (!asack.empty()){
		auto val=asack.getOut();
		auto it=find(v.begin(),v.end(),val);
		ASSERT(it != v.end());
		v.erase(it);
	}
	ASSERT(v.empty());
	std::vector<double> vd{asack};
	ASSERT_EQUAL(asack.size(),vd.size());
}
void asVectorTest(){
	Sack<int> asack = sackForTest();
	auto v=asack.asVector();
	auto vd=asack.asVector<double>();
	ASSERT_EQUAL(asack.size(),v.size());
	ASSERT(equal(v.begin(),v.end(),vd.begin()));
}

void createSackFromInitializerList(){
	Sack<char> csack{'a','b','c'};
	ASSERT_EQUAL(3,csack.size());
}

void makeSackFromInitializerList(){
	auto asack=makeSack({1,2,3,4});
	asack.putInto(5);
	ASSERT_EQUAL(5,asack.size());
}
void makeSackFromHeterogeneousInitializerFails(){
//	auto failstoCompile=makeSack({1,2.0});
}

void makeSackWithLoop(){
	auto asack=makeSack1({'a','b','c'});
	ASSERT_EQUAL(3,asack.size());
}
void makeASackFromAList(){
	Sack<int,std::list> listsack{1,2,3,4,5};
	listsack.getOut();
	listsack.putInto(42);
	ASSERT_EQUAL(5,listsack.size());
}



void createOtherSack() {
	auto intsack=makeSack({1,2,3});
	ASSERT_EQUAL(3,intsack.size());
	ASSERT((std::is_same<int,decltype(intsack.getOut())>::value));
	Sack<int,std::deque> anothersack{};
	auto othersack=makeOtherSack<std::deque>({1,2,3});
	ASSERT_EQUAL(3,othersack.size());
	auto setsack=makeOtherSack<std::set>({'a','b','c','c'});
	ASSERT_EQUAL(3,setsack.size());
}


void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(demoInheritingClassTemplateNameResolutionProblem));
	s.push_back(CUTE(defaultConstructorStillWorks));
	s.push_back(CUTE(extractAVectorFromSack));
	s.push_back(CUTE(asVectorTest));
	s.push_back(CUTE(createSackFromInitializerList));
	s.push_back(CUTE(makeSackFromInitializerList));
	s.push_back(CUTE(makeSackFromHeterogeneousInitializerFails));
	s.push_back(CUTE(makeSackWithLoop));
	s.push_back(CUTE(creationAlsoAllowsTwoInts));
	s.push_back(CUTE(creationAlsoAllowsTwoInts2));
	s.push_back(CUTE(makeASackFromAList));
	s.push_back(CUTE(createOtherSack));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}

