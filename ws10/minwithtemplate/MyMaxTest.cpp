#include "MyMax.h"
#include <ostream>
#include <string>
void MyMaxTest(std::ostream &out){
	using MyMax::max;
	int i = 88;
	out << "max(i,42) = " << max(i,42) << '\n';
	double pi = 3.1415;
	double e = 2.7182;
	out << "max(e,pi) = " << max(e,pi) << '\n';
	std::string s1 = "Hallo";
	std::string s2 = "Hallihallo";
	out << "max(Hallo,Hallihallo) = " << MyMax::max(s1,s2)<<'\n';
	//max(2,pi); // compile error
	max(static_cast<double>(2),pi);
	out << "max(Peter,Toni) = "
		 << max("Peter","Toni") << '\n';
	out << "max<string>(Peter,Toni) = "
		 << max<std::string>("Peter","Toni") << '\n';
}
