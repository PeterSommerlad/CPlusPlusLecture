#include <iostream>
using namespace std;

template <typename T>
void *makeOpaque(T *ptr){
	return ptr;
}

template <typename T>
T *ptrCast(void *p){
	return static_cast<T*>(p);
}


int main() {
	int i{42};
	void * const pi{makeOpaque(&i)};
	cout << *ptrCast<int>(pi)<< endl;
}
