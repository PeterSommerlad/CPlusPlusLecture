#include <type_traits>

template<typename T, typename U>
void assert_same_type(T const &, U const &) {
	static_assert(std::is_same_v<T, U>);
}

int main() {
	int int_value = 1;
	auto auto_value = 2;
	assert_same_type(int_value, auto_value);

	int another_int{3};
	auto whats_my_type{4};
	assert_same_type(another_int, whats_my_type);
}
