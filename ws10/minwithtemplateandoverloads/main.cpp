#include "MyMin.h"
#include <iostream>
#include <string>
int main(){
	using MyMin::min;
	using std::cout;
	int i = 88;
	cout << "min(i,42) = " << min(i,42) << '\n';
	double pi = 3.1415;
	double e = 2.7182;
	cout << "min(e,pi) = " << min(e,pi) << '\n';
	std::string s1 = "Hallo";
	std::string s2 = "Hallihallo";
	cout << "min(Hallo,Hallihallo) = " << MyMin::min(s1,s2)<<'\n';
	//min(2,pi); // compile error
	min(static_cast<double>(2),pi);
	min<double>(2,pi);
	cout << "min(Peter,Toni) = " << min("Peter","Toni") << '\n';
	cout << "min(Pete,Toni) = " << min("Pete","Toni") << '\n';
	void MyMaxTest(std::ostream &);MyMaxTest(std::cout);
}
