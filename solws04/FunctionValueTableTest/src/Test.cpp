#include "funcval.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <iomanip>
#include <cmath>

double square(double x){
	return x*x;
}

void testSimpleFunctionTable(){
	std::ostringstream out{};
	out << std::setprecision(1) << std::fixed;
	printFunctionTable(out,1,3,3,square);
	ASSERT_EQUAL("x\t1.0\t2.0\t3.0\t\n"
                 "f(x)\t1.0\t4.0\t9.0\t\n",out.str());
}

void demoUsageWithTrigonometricFunctions(){
// this code would go into a main() function in the real question
	std::ostringstream out{};
	std::string const expected {R"(
x	0.000000	0.174533	0.349066	0.523599	0.698132	0.872665	1.047198	1.221730	1.396263	1.570796	1.745329	1.919862	2.094395	2.268928	2.443461	2.617994	2.792527	2.967060	3.141593	
f(x)	0.000000	0.173648	0.342020	0.500000	0.642788	0.766044	0.866025	0.939693	0.984808	1.000000	0.984808	0.939693	0.866025	0.766044	0.642788	0.500000	0.342020	0.173648	0.000000	
x	0.000000	0.174533	0.349066	0.523599	0.698132	0.872665	1.047198	1.221730	1.396263	1.570796	1.745329	1.919862	2.094395	2.268928	2.443461	2.617994	2.792527	2.967060	3.141593	
f(x)	1.000000	0.984808	0.939693	0.866025	0.766044	0.642788	0.500000	0.342020	0.173648	0.000000	-0.173648	-0.342020	-0.500000	-0.642788	-0.766044	-0.866025	-0.939693	-0.984808	-1.000000	
x	-1.570796e+00	-1.396263e+00	-1.221730e+00	-1.047198e+00	-8.726646e-01	-6.981317e-01	-5.235988e-01	-3.490659e-01	-1.745329e-01	0.000000e+00	1.745329e-01	3.490659e-01	5.235988e-01	6.981317e-01	8.726646e-01	1.047198e+00	1.221730e+00	1.396263e+00	1.570796e+00	
f(x)	-1.633124e+16	-5.671282e+00	-2.747477e+00	-1.732051e+00	-1.191754e+00	-8.390996e-01	-5.773503e-01	-3.639702e-01	-1.763270e-01	0.000000e+00	1.763270e-01	3.639702e-01	5.773503e-01	8.390996e-01	1.191754e+00	1.732051e+00	2.747477e+00	5.671282e+00	1.633124e+16	
)"};
	out << std::setprecision(6) ; out << std::fixed << '\n';
	auto const pi = std::acos(-1.0);
	printFunctionTable(out,0,pi,19,std::sin);
	printFunctionTable(out,0,pi,19,std::cos);
	out << std::scientific;
	printFunctionTable(out,-pi/2,pi/2,19,std::tan);
	ASSERT_EQUAL(expected,out.str());
}




void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testSimpleFunctionTable));
	s.push_back(CUTE(demoUsageWithTrigonometricFunctions));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



