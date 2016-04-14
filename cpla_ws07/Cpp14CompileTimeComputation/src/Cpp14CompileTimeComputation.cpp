#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
template <unsigned n>
struct fact{
	static unsigned const value{ n * fact<n-1>::value};
};
template <>
struct fact<0>{
	static unsigned const value=1;
};
template <unsigned n>
constexpr unsigned long long fac={n*fac<n-1>};
template <>
constexpr unsigned long long fac<0>{1};

int a[fact<5>::value] { }; // check if compile-time constant
int b[fac<5>] { };

constexpr auto factorial(unsigned n){
	unsigned long long res{1};
	while(n>1) res*=n--;
	return res;
}

namespace compile_time{
template <typename T>
constexpr auto abs(T x){ return x<0?-x:x;}

static_assert(5==abs(-5),"abs is correct for negative int");
static_assert(5==abs(5),"abs is correct for int");
static_assert(5.0==abs(-5.0),"abs is correct for negative double");
static_assert(5.0l==abs(-5.0l),"abs is correct for negative long double");
}


static_assert(fac<20> ==factorial(20),"see if loop computes correct");

void tupledemo() {
	ASSERT_EQUAL(120,fac<5>); // here the parser doesn't evaluate fac<5> (yet)
	ASSERT_EQUAL(120ull,factorial(5));
	ASSERT_EQUAL(fac<20>,factorial(20));
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(tupledemo));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



