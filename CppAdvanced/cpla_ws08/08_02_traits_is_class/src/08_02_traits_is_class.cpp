#include <iostream>
#include <type_traits>


struct S;
int main() {
    using namespace std;
	cout << boolalpha << is_class_v<S> << is_class_v<int>;
	return 0;
}
