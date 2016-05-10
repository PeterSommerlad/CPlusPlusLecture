#include <typeinfo>
#include <type_traits>
#include <iostream>

// used to swallow up superflous template arguments but check their validity
template <typename ...>
using void_t=void; // in std:: in C++17

// helper see also N4502
template <typename, template <typename> class, typename = void_t<>>
struct detect : std::false_type {};

template <typename T, template <typename> class Op>
struct detect<T, Op, void_t<Op<T>>> : std::true_type {};

template <typename T>
using has_ostream_shift_t=decltype(std::declval<std::ostream&>()<<std::declval<T>());

template <typename T>
using is_outputtable = detect<T,has_ostream_shift_t>;

template <typename T, typename = std::enable_if_t<is_outputtable<T>{}>>
void printer(std::ostream & out, T const &t){
	out << t <<'\n';
}
template <typename T >
void printer(std::ostream & out,T const &t
		, std::enable_if_t<not is_outputtable<T>::value>* =nullptr){
	out << "cannot print "<< typeid(T).name() << '\n';
}

int main(){
	struct X{};
	std::cout << "int is "<< is_outputtable<int>{} << std::endl;
	std::cout << "X is "<< is_outputtable<X>{}<<std::endl;

	printer(std::cout , 42);
	printer(std::cout, X{});
	printer(std::cout , std::cout);
}
