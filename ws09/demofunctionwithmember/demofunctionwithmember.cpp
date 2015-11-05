#include <functional>
#include <iostream>

struct X {
	int calc(int i) const { return x*i; }
private:
	int x{7};
};

int main(){
	std::function<int (X const &,int)> const f{&X::calc};
	X const anX{};
	std::cout << f(anX,6);
}
