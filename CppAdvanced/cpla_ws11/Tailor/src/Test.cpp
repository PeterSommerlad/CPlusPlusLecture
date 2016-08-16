#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "tailor_sin.h"
namespace tables {
using tailor::sin;
using namespace tailor::detail;

template <typename T, size_t ...indices>
constexpr auto 
make_sine_table_impl(std::index_sequence<indices...>){
	static_assert(sizeof...(indices)>1,
			"must have 2 values to interpolate");
	return std::array<T,sizeof...(indices)>{{
		sin(indices*two_pi<T>/T(sizeof...(indices)-1))...
	}};
}

template <size_t n, typename T=long double>
constexpr auto make_sine_table=
		make_sine_table_impl<T>(std::make_index_sequence<n>{});
}

using namespace tailor::detail;


constexpr double sinepihalf = tailor::sin(tailor::pi<long double>/2.0l);
constexpr double cosinepi = tailor::cos(tailor::pi<long double>);
constexpr auto sine30degrees = tailor::sin(tailor::degrees<30>);
static_assert(tailor::detail::abs(0.5l- sine30degrees)<1e-16," sine 30 Grad is half");

constexpr auto berlinAndelsHotelNorth=tailor::degrees<52,31,42>;
constexpr auto berlinAndelsHotelWest=tailor::degrees<13,27,17>;


static_assert(sinepihalf==1.0l,"sine pi half is not one");
static_assert(cosinepi==-1.0l,"cosine pi is not minus one");

constexpr auto testsinetab=tables::make_sine_table<5,long double>;
static_assert(testsinetab[0]==0.0, "sine 0 is 0");
static_assert(abs(testsinetab[2])<1e-10, "sine pi is 0");
static_assert(abs(testsinetab.back()) <1e-10, "sine two pi is 0");
static_assert(abs(testsinetab[1]-1.0)<1e-10, "sine pi/2 is 1");
static_assert(abs(testsinetab[3]+1.0)<1e-10, "sine pi+pi/2 is -1");

void testsineTableTest(){
	long double eps { 1e-10l };
	ASSERT_EQUAL(0.0,testsinetab[0]);
	ASSERT_EQUAL_DELTA(1.0,testsinetab[1],eps);
	ASSERT_EQUAL_DELTA(0.0,testsinetab[2],eps);
	ASSERT_EQUAL_DELTA(-1.0,testsinetab[3],eps);
	ASSERT_EQUAL_DELTA(0.0,testsinetab[4],eps);

}
using tailor::detail::abs;

constexpr auto largesinetab=tables::make_sine_table<360+1 ,double>;
// limited to 1 degree -fconstexpr-steps=larger to get more
static_assert(largesinetab.front()==0,"sine 0 is 0");
static_assert(abs(largesinetab.back())<1e-12,"sine 2 pi is 0");
static_assert(abs(largesinetab[90]-1)<1e-12,"sine 90 degree is 1");
static_assert(abs(largesinetab[180])<1e-12,"sine 180 degree is 0");
static_assert(abs(largesinetab[270]+1)<1e-12,"sine 270 degree is 1");

void testsine() {

	ASSERT_EQUAL(0.0l, tailor::sin(0.0l));
	for (long double i = -3.15e2l; i <= 3.15e2l; i += 0.1) {
		std::string msg=std::to_string(i) + " sine wrong ";
		ASSERT_EQUAL_DELTAM(msg,std::sin(i), tailor::sin(i), 1e-12l);
	}
}
void testcosine() {

	ASSERT_EQUAL(1.0l, tailor::cos(0.0l));
	for (long double i = -3.15e2l; i <= 3.15e2l; i += 0.1) {
		std::string msg=std::to_string(i) + " cosine wrong ";
		ASSERT_EQUAL_DELTAM(msg,std::cos(i), tailor::cos(i), 1e-12l);
	}
}
void showSineTable(){
	for (size_t i=0; i <= 90 ; ++i){
		std::cout << i << "  "<<largesinetab[i]<<'\n';
	}
	ASSERTM("start writing tests", false);
}



constexpr long double val1=1.0l+37*two_pi<long double>;
constexpr long double val2=2.0l+33*two_pi<long double>;
constexpr long double val3=3.0l+38*two_pi<long double>;
void testAdjustToPi(){
	ASSERT_EQUAL_DELTA(1.0l,adjust_to_two_pi(val1),1e-15);
	ASSERT_EQUAL_DELTA(-1.0l,adjust_to_two_pi(-val1),1e-15);
	ASSERT_EQUAL_DELTA(2.0l,adjust_to_two_pi(val2),1e-15);
	ASSERT_EQUAL_DELTA(-2.0l,adjust_to_two_pi(-val2),1e-15);
	ASSERT_EQUAL_DELTA(3.0l,adjust_to_two_pi(val3),1e-15);
	ASSERT_EQUAL_DELTA(-3.0l,adjust_to_two_pi(-val3),1e-15);
}


void testfak() {
	ASSERT_EQUAL(1.0L, fak(0));
	ASSERT_EQUAL(1.0L, fak(1));
	ASSERT_EQUAL(2.0L, fak(2));
	ASSERT_EQUAL(6.0L, fak(3));
	ASSERT_EQUAL(24.0L, fak(4));
	ASSERT_EQUAL(120.0L, fak(5));
	ASSERT_EQUAL(720.0L, fak(6));
	ASSERT_EQUAL(2432902008176640000.0L, fak(20)); // up to n=10 -> fak(21) exact enough
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testfak));
	s.push_back(CUTE(testsine));
	s.push_back(CUTE(testcosine));
	s.push_back(CUTE(testAdjustToPi));
	s.push_back(CUTE(testsineTableTest));
	//s.push_back(CUTE(showSineTable));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

