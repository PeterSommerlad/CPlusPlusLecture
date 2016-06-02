#include <iostream>

template <typename T>
bool concept is_red() {
	return requires (T a) {
	a.red();
};
}
template <typename T>
bool concept is_green() {
	return requires (T a) {
	++a;
};
}

template <typename T>
requires is_green<T>() 
auto doit(T t){
std::cout << "doit with green\n";
return ++t;
}
template <typename T>
requires is_green<T>()  && is_red<T>()
auto doit(T t){
std::cout << "doit with orange\n";
return ++t;
}

template <typename T>
auto doit(T t) {
std::cout << "doit without green\n";
return t;
}
template <typename T>
requires is_red<T>()
auto doit(T t) {
std::cout << "doit with red\n";
return t;
}

struct Red{void red() const {}};
struct Green:Red{void operator++(){}};
struct Blue{};

int main(){
	doit(5);
	doit(Red{});
	doit(Green{});
	doit(Blue{});
}
