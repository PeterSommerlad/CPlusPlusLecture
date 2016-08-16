#include "lessthan.h"

template<LessThanComparable T>
T const &min(T const &a, T const &b){
	return (a<b)?a:b;
}

template<typename T>
requires LessThanComparable<T>()
T const &max(T const &a, T const &b){
	return (a < b)?b:a;
}
struct X{};
void operator<(X,X){}
int main(){
	min(3,4);
	max(5.0,6.0);
	//min(X{},X{}); // concept check fails
}
