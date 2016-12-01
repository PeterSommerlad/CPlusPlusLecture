#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "primes.h"
#include <sstream>

/*
 * Implement the is_prime and primes functions.
 * is_prime: checks for a given number whether it is prime or not
 * primes: prints all prime numbers below a given limit to an std::ostream
 *
 * Add more tests below.
 *
 * This file contains two main() functions. One for running the tests, the other for running using
 * the primes() with the standard output.
 */


void test_two_is_prime() {
	ASSERTM("Expected 2 to be prime", is_prime(2));
}

void test_print_primes_up_to_two() {
	std::ostringstream output{};
	primes(output, 2);
	ASSERT_EQUAL("", output.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_two_is_prime));
	s.push_back(CUTE(test_print_primes_up_to_two));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}


//int main(int argc, char **argv) {
//	primes(std::cout, 1000);
//}
