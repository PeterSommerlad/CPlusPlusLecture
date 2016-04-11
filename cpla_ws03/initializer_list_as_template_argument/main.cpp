#include <initializer_list>

template<typename T>
void f(T param) {

}


int main(int argc, char **argv) {
	f({23, 24}); // compile error!
}
