#include "Ring5.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
void testDefaultCtor() {
    Ring5 v{};
    ASSERT_EQUAL(0,v.value());
}
void testValueCtor(){
    Ring5 four{4};
    ASSERT_EQUAL(4,four.value());
}
// operator==, operator<< for failures
void testValueCtorWithLargeInput(){
    Ring5 four{19};
    ASSERT_EQUAL(Ring5{4},four);
}
// define operator<< format
void testOutputOperator(){
    std::ostringstream out;
    out << Ring5{4};
    ASSERT_EQUAL("Ring5{4}",out.str());
}

void testAddition() {
    Ring5 two{2};
    Ring5 four = two+two;
    ASSERT_EQUAL(4,four.value());
}
void testAdditionWrap(){
    Ring5 four{4};
    Ring5 three = four + four;
    ASSERT_EQUAL(3,three.value());
}

void testMultiplication(){
    Ring5 four{4};
    Ring5 three{3};
    Ring5 two = four * three;
    ASSERT_EQUAL(Ring5{2},two);
}








void testAdditionWithInt(){
//*
    Ring5 two{2};
    auto four=two+Ring5{2};
    ASSERT_EQUAL(Ring5{4},four);
    ASSERT_EQUAL(typeid(Ring5).name(),
                 typeid(decltype(four)).name());
//*/
}

void testAssignmentBackToInt(){
    Ring5 three{8};
    unsigned u3=three;
//*
    unsigned eight= three+5u;
    ASSERT_EQUAL(8u,eight);
//*/
    ASSERT_EQUAL(3u,three);
    ASSERT_EQUAL(3u,u3);
}

void testAdditionWithIntExplicitCtor(){
    Ring5 two{2};
    auto four=two+Ring5{2u};
    ASSERT_EQUAL(Ring5{4},four);
    ASSERT_EQUAL(typeid(Ring5).name(),
                 typeid(decltype(four)).name());
}



void testAssignmentBackToIntExplicitCtor(){
    Ring5 three{8};
    unsigned u3=three;
    auto eight= three+5u;
    ASSERT_EQUAL(8u,eight);
    ASSERT_EQUAL(3u,u3);
    ASSERT_EQUAL(3u,three);
}

static_assert(Ring5{2}==Ring5{4}+Ring5{3},
              "constexpr addition, equal and ctor");
static_assert(Ring5{}!=Ring5{4}*Ring5{3},
              "constexpr multiplication unequal");
static_assert(2u==(Ring5{4}*Ring5{3}).value(),
              "constexpr value()");
static_assert(2u==unsigned{Ring5{4}*Ring5{3}},
              "constexpr conversion");
constexpr
auto dont_call_this_way=R5::operator"" _R5(42);
using R5::operator"" _R5;// or using namespace R5;
static_assert(Ring5{2}==7_R5,"UDL operator");

static_assert(2==2_R5,"explicit UDL operator worked");



void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
    s.push_back(CUTE(testDefaultCtor));
    s.push_back(CUTE(testValueCtor));
    s.push_back(CUTE(testValueCtorWithLargeInput));
    s.push_back(CUTE(testAddition));
    s.push_back(CUTE(testAdditionWrap));
    s.push_back(CUTE(testOutputOperator));
    s.push_back(CUTE(testMultiplication));
    s.push_back(CUTE(testAdditionWithInt));
    s.push_back(CUTE(testAssignmentBackToInt));
    s.push_back(CUTE(testAdditionWithIntExplicitCtor));
    s.push_back(CUTE(testAssignmentBackToIntExplicitCtor));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



