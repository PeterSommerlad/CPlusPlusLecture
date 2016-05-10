
#include <iostream>
#include <array>
#include <vector>

using One=char;
using Two=struct{char x[2];};
static_assert(sizeof(One)!= sizeof(Two)
		,"assume One and Two have different sizes");

template <typename T>
class IsClass{
	template<typename C> static
	One check(int C::*); // member pointer
	template<typename C> static
	Two check(...); // catch all
public:
	constexpr static bool
	value{sizeof(IsClass<T>::check<T>(0))==sizeof(One)};
};

struct X{
};

int main() {
	using namespace std;
	cout << boolalpha;
	cout << "int is_class: " << IsClass<int>::value << endl;
	cout << "X is_class: " << IsClass<X>::value << endl;
	cout << "vector<int>::iterator is_class: "
		 << IsClass<decltype(vector<int> {}.begin())>::value << endl;
	cout << "array<int>::iterator is_class: "
		 << IsClass<decltype(array<int,1> {}.begin())>::value << endl;
	return 0;
}
