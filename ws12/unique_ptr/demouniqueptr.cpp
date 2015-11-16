#include <memory>
#include <iostream>

struct X{
	X(int i):x{i}{}
	int x;
	virtual ~X(){std::cout << "X deleted\n";}
}; // a dummy type for demonstration

struct Y : X {
	Y(int i):X{-i},d{3.14}{}
	double d;
	~Y(){std::cout << "Y deleted\n";}
};

std::unique_ptr<X> factory(int i){
	if (i < 0)
		return std::make_unique<Y>(i);
	return std::make_unique<X>(i);
}

int main(){
	auto x=factory(42);
	std::cout << (*x).x << '\n';
	std::cout << x->x << '\n';
	std::cout << (*x.get()).x << '\n';

	auto y=factory(-1);
	std::cout << (*y).x << '\n';
}
