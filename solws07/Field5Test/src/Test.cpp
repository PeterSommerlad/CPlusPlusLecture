#include "Field5.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
void testDefaultCtor() {
    Field5 v{};
    ASSERT_EQUAL(0,v.value());
}
void testValueCtor(){
    Field5 four{4};
    ASSERT_EQUAL(4,four.value());
}
// operator==, operator<< for failures
void testValueCtorWithLargeInput(){
    Field5 four{19};
    ASSERT_EQUAL(Field5{4},four);
}
// define operator<< format
void testOutputOperator(){
    std::ostringstream out;
    out << Field5{4};
    ASSERT_EQUAL("Field5{4}",out.str());
}

void testAddition() {
    constexpr Field5 two{2};
    constexpr Field5 four = two+two;
    static_assert(4==four.value(),"addition failed");
    ASSERT_EQUAL(4,four.value());
}
void testAdditionWrap(){
    Field5 four{4};
    Field5 three = four + four;
    ASSERT_EQUAL(3,three.value());
}

void testMultiplication(){
    Field5 four{4};
    Field5 three{3};
    Field5 two = four * three;
    ASSERT_EQUAL(Field5{2},two);
}








void testAdditionWithInt(){
//*
    Field5 two{2};
    auto four=two+Field5{2};
    ASSERT_EQUAL(Field5{4},four);
    ASSERT_EQUAL(typeid(Field5).name(),
                 typeid(decltype(four)).name());
//*/
}

void testAssignmentBackToInt(){
    Field5 three{8};
    unsigned u3=three;
//*
    unsigned eight= three+5u;
    ASSERT_EQUAL(8u,eight);
//*/
    ASSERT_EQUAL(3u,three);
    ASSERT_EQUAL(3u,u3);
}

void testAdditionWithIntExplicitCtor(){
    Field5 two{2};
    auto four=two+Field5{2u};
    ASSERT_EQUAL(Field5{4},four);
    ASSERT_EQUAL(typeid(Field5).name(),
                 typeid(decltype(four)).name());
}



void testAssignmentBackToIntExplicitCtor(){
    Field5 three{8};
    unsigned u3=three;
    auto eight= three+5u;
    ASSERT_EQUAL(8u,eight);
    ASSERT_EQUAL(3u,u3);
    ASSERT_EQUAL(3u,three);
}

void testSubtract(){
	Field5 four{4};
	Field5 one{1};
	ASSERT_EQUAL(Field5{3},four-one);
	ASSERT_EQUAL(Field5{2},one-four);
}

void testDivision(){
	Field5 four{4};
	ASSERT_EQUAL(Field5{1},four/four);
	ASSERT_EQUAL(Field5{2},four/Field5{2});
	ASSERT_EQUAL(Field5{3},four/Field5{3});
	ASSERT_EQUAL(four,four/Field5{1});
	ASSERT_EQUAL(four,Field5{2}/Field5{3});
	ASSERT_EQUAL(four,Field5{3}/Field5{2});
}


static_assert(Field5{2}==Field5{4}+Field5{3},
              "constexpr addition, equal and ctor");
static_assert(Field5{}!=Field5{4}*Field5{3},
              "constexpr multiplication unequal");
static_assert(2u==(Field5{4}*Field5{3}).value(),
              "constexpr value()");
static_assert(2u==unsigned{Field5{4}*Field5{3}},
              "constexpr conversion");


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
	s.push_back(CUTE(testSubtract));
	s.push_back(CUTE(testDivision));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



