#include "MyMax.h"
#include <iostream>
#include <string>
void MyMaxTest(){
	using MyMax::max;
	using std::cout;
	int i = 88;
	cout << "max(i,42) = " << max(i,42) << '\n';
	double pi = 3.1415;
	double e = 2.7182;
	cout << "max(e,pi) = " << max(e,pi) << '\n';
	std::string s1 = "Hallo";
	std::string s2 = "Hallihallo";
	cout << "max(Hallo,Hallihallo) = " << MyMax::max(s1,s2)<<'\n';
	//max(2,pi); // compile error
	max(static_cast<double>(2),pi);
	cout << "max(Peter,Tobi) = "
		 << max("Peter","Tobi") << '\n';
	cout << "max<string>(Peter,Tobi) = "
		 << max<std::string>("Peter","Tobi") << '\n';
}
