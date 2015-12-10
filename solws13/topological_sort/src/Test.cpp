#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"


#include "module.h"



#include "module_sort.h"

void test_module_nodeps(){
	module m{"OO"};
	ASSERT(m.is_ready());
	ASSERT_EQUAL(module{"OO"},m);
	ASSERT_LESS(module{"AA"},m);
}

void test_module_deps(){
	spm oo = make_module("OO");
	spm ad1 = make_module("AD1");
	ad1->add(oo);
	ASSERT(!ad1->is_ready());
	ad1->done_with(oo);
	ASSERT(ad1->is_ready());
}


void test_deep_name_comare(){
	spm l=make_module("AA");
	spm r=make_module("BB");
	deep_name_compare cmp{};
	ASSERT(cmp(l,r));
	ASSERT(!cmp(r,l));
	ASSERT(!cmp(l,l));
	ASSERT(cmp(nullptr,l));
	ASSERT(!cmp(l,nullptr));
	ASSERT(!cmp(nullptr,nullptr));
}






std::string const input {
R"(
DB1 OO
DB2 DB1
Math
OO
AD1 OO
CPI OO Math
Thesis DB2 SE2 UI2
SE1 AD1 CPI DB1
SE2 DB1 SE1 UI1
UI1 AD1
UI2 UI1
)"
};
void testinput(){
	std::istringstream is{input};
	module_sort ms{is};
	ASSERT_EQUAL(11,ms.all_modules.size());
}

struct equal_name{
	equal_name(char const *n):name{n}{}
	std::string name;
	bool operator()(spm m){
		return bool(m) && m->name == name;
	}
};

template <typename RESULT>
bool result_contains(RESULT res,char const * name){
	return end(res) != find_if(begin(res),end(res),equal_name{name} );
}

void testLevel1(){
	std::istringstream is{input};
	module_sort ms{is};
	auto res=ms.next_level();
	ASSERT_EQUAL(9,ms.all_modules.size());

	ASSERT_EQUAL(2,res.size());
	ASSERT(result_contains(res,"Math"));
	ASSERT(result_contains(res,"OO"));
}

void testLevel2(){
	std::istringstream is{input};
	module_sort ms{is};
	ms.next_level();
	ASSERT_EQUAL(9,ms.all_modules.size());
	auto res=ms.next_level();
	ASSERT_EQUAL(3,res.size());
	ASSERT(result_contains(res,"AD1"));
	ASSERT(result_contains(res,"CPI"));
	ASSERT(result_contains(res,"DB1"));
}

void testLevel3(){
	std::istringstream is{input};
	module_sort ms{is};
	ms.next_level();
	ms.next_level();
	ASSERT_EQUAL(6,ms.all_modules.size());
	auto res=ms.next_level();
	ASSERT_EQUAL(3,res.size());
	ASSERT(result_contains(res,"DB2"));
	ASSERT(result_contains(res,"SE1"));
	ASSERT(result_contains(res,"UI1"));
}

void testLevel4(){
	std::istringstream is{input};
	module_sort ms{is};
	ms.next_level();
	ms.next_level();
	ms.next_level();
	ASSERT_EQUAL(3,ms.all_modules.size());
	auto res=ms.next_level();
	ASSERT_EQUAL(2,res.size());
	ASSERT(result_contains(res,"UI2"));
	ASSERT(result_contains(res,"SE2"));
}

void testLevel5(){
	std::istringstream is{input};
	module_sort ms{is};
	ms.next_level();
	ms.next_level();
	ms.next_level();
	ms.next_level();
	ASSERT_EQUAL(1,ms.all_modules.size());
	auto res=ms.next_level();
	ASSERT_EQUAL(1,res.size());
	ASSERT(result_contains(res,"Thesis"));
	ASSERT_EQUAL(0,ms.all_modules.size());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(test_module_nodeps));
	s.push_back(CUTE(test_module_deps));
	s.push_back(CUTE(test_deep_name_comare));
	s.push_back(CUTE(testinput));
	s.push_back(CUTE(testLevel1));
	s.push_back(CUTE(testLevel2));
	s.push_back(CUTE(testLevel3));
	s.push_back(CUTE(testLevel4));
	s.push_back(CUTE(testLevel5));
	//s.push_back(CUTE(testLevel2));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



