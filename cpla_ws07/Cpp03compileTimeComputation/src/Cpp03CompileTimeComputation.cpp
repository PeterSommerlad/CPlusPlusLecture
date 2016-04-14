#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

const size_t SZ=6*7;
double x[SZ];


template <size_t n>
struct fact{
	static size_t const value=( n * fact<n-1>::value);
};
template <>
struct fact<0>{
	static size_t const value=1;
};

int a[fact<5>::value]; // check compile-time constant

void testFactorialCompiletime() {
	ASSERT_EQUAL(sizeof(a),sizeof(int)*2*3*4*5);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testFactorialCompiletime));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



