#include <iostream>


struct X {
	void foo(std::ostream &out) const { out << a << " foo\n"; }
	void bar(std::ostream &out) const { out << b << " bar\n"; }
	int a;
	int b;
};

void doit(void (X::*mfunc)(std::ostream &) const, X const &x, std::ostream &out){
	(x.*mfunc)(out); // parenthesis needed
}

void change(int X::*memvar, X& x, int val){
	x.*memvar = val;
}


int main(){
	X x{1,2};
	doit(&X::foo,x,std::cout);
	doit(&X::bar,x,std::cout);
	change(&X::a,x,42);
	change(&X::b,x,43);
	doit(&X::foo,x,std::cout);
	doit(&X::bar,x,std::cout);
}
