#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <vector>
	void showScopingRules(int,double);
	void localReferencesExample();
	std::string serialize(std::vector<int> const &v);
#if q
	int main(){
		::showScopingRules(42,3.14);
		localReferencesExample();
		std::cout << serialize(std::vector<int>{3,1,4,1,5,9,2,6}) << "\n";
	}
#endif



double square(double value) {
	return value*value;
}







template <typename T>
auto square(T value) -> decltype(value*value) {
	return value*value;
}






void printValue(std::ostream &out,int value)
{
	out << value;
}




void localReferencesExample()
{
	int i{42};
	int &ri{i}; // must initialize ref
	int const &cri{i}; // const alias
	int const &cr{6*7}; // extend lifetime of 6*7
	ri = 43; // changes i, ri only an alias
	//--cri ; // doesn't work -> const
	int &&rvr{3*14}; // extends lifetime of 3*14
	//int &&rvri{i}; // impossible
	int &&rvri{std::move(i)}; // steal i's content

	std::cout << i << '\n'; // to avoid warnings
	std::cout << ri << '\n';
	std::cout << cri << '\n';
	std::cout << cr << '\n';
	std::cout << rvr << '\n';
	std::cout << rvri << '\n';


}
#if 0
std::ofstream fileFactory(std::string filename){
	std::ofstream theFile(filename.c_str());
	return theFile;
}
#endif





std::string serialize(std::vector<int> const &v){
	std::ostringstream out;
	using outiter=std::ostream_iterator<int>;
	copy(v.begin(),v.end(),outiter(out,", "));
	return out.str();
}









void demoAmbiguity() ;
int main() {
	showScopingRules(42, 3.14);
	localReferencesExample();
	std::cout << serialize(std::vector<int> { 3, 1, 4, 1, 5, 9, 2, 6 }) << "\n";
	demoAmbiguity();
	std::cout << std::log(-1.0);
}







void increment(int &i){
	++i; // side effect on argument
}







int plusOne(int i){
	return i+1;
}






void useIncrementAndPlusOne(){
	int j{42};
	increment(j);
	j = plusOne(j);
}





void demoLambdaFunction(){
	auto const f=
	[](int i){return i+1;};
	auto const g=
	[](char c)->int{return std::toupper(c);};
	g('a');
	f(42);
}
