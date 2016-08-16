#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

namespace velocity {

constexpr double MPH_TO_KMH { 1.60934 };

struct speed {
	constexpr
	explicit
	speed(long double kmh) :
			kmh { kmh } {
	}
	operator long double() const {
		return kmh;
	}
	long double const kmh;
};

constexpr speed operator"" _kmh(long double kmh) {
	return speed { kmh };
}

constexpr speed operator"" _kmh(unsigned long long kmh) {
	return speed { static_cast<long double>(kmh) };
}

constexpr speed operator"" _mph(long double mph) {
	return speed { mph * MPH_TO_KMH };
}
}

using namespace velocity;

void declarations_for_speed() {
	speed s1 { 5.0 };
//	speed s2 = 5.0;
	auto s3 = 5.0;
	auto s4 = speed { 5.0 };
	auto s5 = speed { 5.0 * MPH_TO_KMH };
	auto s6 = 5.0_kmh;
	auto s7 = 5.0_mph;
}

void test_kmh_operator() {
	auto s = 5.0_kmh;
	ASSERT_EQUAL_DELTA(5.0, s, 0.01);
}

void test_kmh_operator_integral() {
	auto s = 5_kmh;
	ASSERT_EQUAL_DELTA(5.0, s, 0.01);
}

void test_mph_operator() {
	ASSERT_EQUAL_DELTA(8.05_kmh, 5.0_mph, 0.01_kmh);
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s;
	s.push_back(CUTE(test_kmh_operator));
	s.push_back(CUTE(test_mph_operator));
	s.push_back(CUTE(test_kmh_operator_integral));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

