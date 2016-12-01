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
	ASSERT_EQUAL("2\n", output.str());
}

void test_print_primes_up_to_three() {
	std::ostringstream output{};
	primes(output, 3);
	ASSERT_EQUAL("2\n3\n", output.str());
}


void test_print_primes_up_to_1000() {
	std::ostringstream output{};
	primes(output, 1000);
	ASSERT_EQUAL("2\n3\n5\n7\n11\n13\n17\n19\n23\n29\n31\n37\n41\n43\n47\n53\n59\n61\n67\n71\n73\n79\n83\n89\n97\n101\n103\n107\n109\n113\n127\n131\n137\n139\n149\n151\n157\n163\n167\n173\n179\n181\n191\n193\n197\n199\n211\n223\n227\n229\n233\n239\n241\n251\n257\n263\n269\n271\n277\n281\n283\n293\n307\n311\n313\n317\n331\n337\n347\n349\n353\n359\n367\n373\n379\n383\n389\n397\n401\n409\n419\n421\n431\n433\n439\n443\n449\n457\n461\n463\n467\n479\n487\n491\n499\n503\n509\n521\n523\n541\n547\n557\n563\n569\n571\n577\n587\n593\n599\n601\n607\n613\n617\n619\n631\n641\n643\n647\n653\n659\n661\n673\n677\n683\n691\n701\n709\n719\n727\n733\n739\n743\n751\n757\n761\n769\n773\n787\n797\n809\n811\n821\n823\n827\n829\n839\n853\n857\n859\n863\n877\n881\n883\n887\n907\n911\n919\n929\n937\n941\n947\n953\n967\n971\n977\n983\n991\n997\n", output.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_two_is_prime));
	s.push_back(CUTE(test_print_primes_up_to_two));
	s.push_back(CUTE(test_print_primes_up_to_three));
	s.push_back(CUTE(test_print_primes_up_to_1000));
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
