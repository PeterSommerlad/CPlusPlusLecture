
#include <type_traits>

template<typename T>
T negate(T t) {
	static_assert(std::is_signed_v<T>);
	static_assert(std::is_signed_v<T>, "negate can only be called on signed types");
	return -t;
}


int main() {
	int answer = 42;
	negate(answer);

	unsigned weight = 100;
	negate(weight);
}
