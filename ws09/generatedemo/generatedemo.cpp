#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>





std::vector<int> vectorwithsquares_lambda(){
	std::vector<int> v;
	int x{}; // memory for lambda below
	generate_n(std::back_inserter(v),10,[&x]{
		++x; return x*x;
	});
	return v;
}


void print(std::vector<int> v, std::ostream& out){
	std::ostream_iterator<int> os{out,", "};
	copy(v.begin(),v.end(),os);
	out << '\n';
}





class make_squares{
	int x{};
public:
	int operator()() { ++x; return x*x; }
};
std::vector<int> vectorwithsquares_functor(){
	std::vector<int> v(10);
	generate(v.begin(),v.end(),make_squares{});
	return v;
}
std::vector<int> vectorwithsquares_mutable_lambda(){
	std::vector<int> v;
	int x{}; // memory for lambda below
	generate_n(std::back_inserter(v),10,[x]() mutable {
		return ++x , x*x; // mutable allows change
	});
	return v;
}


struct DemoLambdaMemberVariables {
	int x{};
	std::vector<int> demoAccessingMemberFromLambda() {
		std::vector<int> v;
		generate_n(back_inserter(v),10,[=] {
			return ++x, x*x; // member x can be changed
		});
		return v;
	}
};


int main(){
	print(vectorwithsquares_lambda(),std::cout);
	print(vectorwithsquares_functor(),std::cout);
	print(vectorwithsquares_mutable_lambda(),std::cout);
	DemoLambdaMemberVariables d { };
	print(d.demoAccessingMemberFromLambda(),std::cout);
}

