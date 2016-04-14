#include <array>

void foo(int a[]){
// how big is a? it is a pointer only
}

template <size_t n>
void bar(std::array<int,n> a){
}

int main(){
	int cube[6]{1,2,3,4,5,6};
	std::array<int,6> cubea{{1,2,3,4,5,6}};
	foo(cube);
	bar(cubea);
}



