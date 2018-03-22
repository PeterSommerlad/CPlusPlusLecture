#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

template<typename T>
void f_value(T t){
	std::cout << "T         = " << boost::typeindex::type_id_with_cvr<T>() << "\n";
	std::cout << "ParamType = " << boost::typeindex::type_id_with_cvr<decltype(t)>() << "\n";
}

template<typename T>
void f_const_ref(T const & t) {
	std::cout << "T         = " << boost::typeindex::type_id_with_cvr<T>() << "\n";
	std::cout << "ParamType = " << boost::typeindex::type_id_with_cvr<decltype(t)>() << "\n";
}

template<typename T>
void f_const_ref_vector(std::vector<T> const & t) {
	std::cout << "T         = " << boost::typeindex::type_id_with_cvr<T>() << "\n";
	std::cout << "ParamType = " << boost::typeindex::type_id_with_cvr<decltype(t)>() << "\n";
}

template<typename T>
void f_fwd_ref(T&& t) {
	std::cout << "T         = " << boost::typeindex::type_id_with_cvr<T>() << "\n";
	std::cout << "ParamType = " << boost::typeindex::type_id_with_cvr<decltype(t)>() << "\n";
}

int main(int argc, char **argv) {
	int i { 5 };
	f_value(i);				//T = int, ParamType = int
	int const &rci { i };
	f_value(rci);			//T = int, ParamType = int

	f_const_ref(rci);		//T = int, ParamType = int const &
	std::vector<int> vi{};
	f_const_ref(vi);		//T = std::vector<int>, ParamType = std::vector<int> const &

	f_const_ref_vector(vi);	//T = int, ParamType = std::vector<int> const &

	f_fwd_ref(i);			//T = int &, ParamType = int &
	f_fwd_ref(5);			//T = int, ParamType = int &&

}
