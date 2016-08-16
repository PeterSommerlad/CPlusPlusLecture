#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

constexpr size_t SZ{7*3*(1+1)};
constexpr double x[SZ]{1,2,3,4,5,6,7,8,3.1415926};
static_assert(sizeof(x)==42*sizeof(double),"size of array x unexpected");
static_assert(x[3]+x[4]==9,"expect x initialized at compile-time");

constexpr unsigned long long fact(unsigned short n) {
	return n>1?n*fact(n-1):1;
}

int a[fact(5)] { };

namespace compile_time{
template <typename T>
constexpr T abs(T x){ return x<0?-x:x;}

static_assert(5==abs(-5),"abs is correct for negative int");
static_assert(5==abs(5),"abs is correct for int");
static_assert(5.0==abs(-5.0),"abs is correct for negative double");
static_assert(5.0l==abs(-5.0l),"abs is correct for negative long double");
}

void testFactorialCompiletime() {
	ASSERT_EQUAL(sizeof(int)*2*3*4*5,sizeof(a));
}
void testSizeOfAndInitOfX(){
	ASSERT_EQUAL(42*sizeof(double),sizeof(x));
	double const *px=x;
	ASSERT_EQUAL(1,*px);
}
constexpr double factd(unsigned short n) {
	return n>1?n*factd(n-1):1;
}
constexpr auto fac5=factd(5);
static_assert(120==fac5,"see if doubles compare equal");
void testFactDouble(){
	int i { 3 + fact(2) };
	ASSERT_EQUAL(120.0,factd(i));
}



void runAllTests(int argc, char const *argv[]){
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testFactorialCompiletime));
	s.push_back(CUTE(testSizeOfAndInitOfX));
	s.push_back(CUTE(testFactDouble));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



