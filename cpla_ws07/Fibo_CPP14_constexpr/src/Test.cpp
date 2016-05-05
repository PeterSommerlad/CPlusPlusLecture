#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <wchar.h>

// std::exchange is not constexpr...
template <typename T, typename V>
constexpr auto exchange(T& var,V && val){
	T const old = std::move(var);
	var = std::forward<V>(val);
	return old;
}


constexpr auto fibo(int n){
	extern char const * const fibo_must_not_be_called_at_run_time;
	size_t f0{0},f1{1};
	if (n < 0) throw fibo_must_not_be_called_at_run_time;
	while(n-->0){
		f0=exchange(f1,f1+f0);
	}
	return f0;
}

static_assert(0==fibo(0),"fibo(0)");
static_assert(1==fibo(1),"fibo(1)");
static_assert(1==fibo(2),"fibo(2)");
static_assert(2==fibo(3),"fibo(3)");
static_assert(3==fibo(4),"fibo(4)");
static_assert(1836'311'903==fibo(46),"fibo(46)");


void thisIsATest() {
//	ASSERT_EQUAL(55,fibo(10));
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



