#include <iostream>
#include <array>
template <typename T, unsigned int EXP>
struct exp{
	T operator()(T const & val) {
		T res = val;
		for (unsigned int i=1; i < EXP; ++i)
			res *= val;
		return res;
	}
};
template <typename T>
struct exp<T,0> {
	T operator()(T const &val){
		return T(1);
	}
};


int main(){
	using namespace std;
	cout << exp<int,2>()(4) << endl;
	cout <<scientific << exp<double,30>()(10) << endl;
	std::array<int,5> a{};
}

