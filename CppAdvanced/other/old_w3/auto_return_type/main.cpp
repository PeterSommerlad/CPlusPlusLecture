#include <iostream>
#include <initializer_list>
#include <boost/type_index.hpp>

//auto createInitList() {
//  return {1,2,3};
//}

auto createInt() { //requires body to be known
	std::cout << "creating int\n";
	return 23;
}

auto const lambda = [](auto p) { //generic lambda
	std::cout << "lambda: type of p: " << boost::typeindex::type_id_with_cvr<decltype(p)>() << "\n";
	return p;
};

void f(auto p) {
	std::cout << "f: type of p: " << boost::typeindex::type_id_with_cvr<decltype(p)>() << "\n";
}

int main(int argc, char **argv) {
	createInt();
	lambda(23);
	lambda(23.0);
	f(23);
	f(23.0);
}

