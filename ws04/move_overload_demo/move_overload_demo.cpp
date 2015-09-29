#include <iostream>

struct X{};

//void foo(X v){ // would make things ambiguous
//	std::cout << "foo(X) \n";
//}
void foo(X& lv){
	std::cout << "foo(X&) \n";
}
void foo(X&& rvr){
	std::cout << "foo(X&&) \n";
}
void foo(X const& rv){
	std::cout << "foo(X const&) \n";
}
void foo(X const && rvr){
	std::cout << "foo(X const &&) \n";
}


int main(){
	X x{};
	X const &y{X{}};
	X &z { x };
	X const a{};
	X &&b{X{}};
	X const &&c{X{}};

	foo(x);
	foo(const_cast<X const&>(x));
	foo(std::move(x)); // mustn't use x afterwards
	foo(y);
	foo(std::move(y)); // no op
	foo(z);
	foo(std::move(z));
	foo(a);
	foo(std::move(a));
	foo(b);
	foo(std::move(b));
	foo(c);
	foo(std::move(c));
}
