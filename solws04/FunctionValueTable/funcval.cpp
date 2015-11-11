#include "funcval.h"
#include <vector>
#include <algorithm>
#include <ostream>
#include <iterator>
#include <iomanip>
void printFunctionTable(std::ostream& out, double b, double e, int steps, double func(double)) {
	std::vector<double> v(steps);
	double const delta { (e - b) / (steps - 1) }; // e is inclusive!
	for (int i=0; i < steps;++i){
		v[i]= b + i*delta;
	} // or could use generate with mutable lambda:
	generate(begin(v),end(v),[b,delta,i=0] () mutable{ return b + (i++)*delta;} );
	out << "x\t";
	std::ostream_iterator<double> oi{out,"\t"};
	copy(begin(v),end(v),oi);
	out << "\nf(x)\t";
	transform(begin(v),end(v),oi,func);
	out << "\n";
}
