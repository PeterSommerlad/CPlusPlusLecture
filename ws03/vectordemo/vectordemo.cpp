#include <vector>
#include <iostream>
#include <iterator>

int main(){
	std::vector<int> v{1,2,3,4,5};

	for (size_t i=0; i < v.size(); ++i){
		std::cout << "v["<<i<<"] = "<< v[i] <<'\n';
	}
	for (std::vector<int>::size_type i=0;
			i < v.size(); ++i){
		std::cout << v.at(i) <<'\n';
	}

	for (auto &j:v){
		j *= 2;
	}
	for (auto const i:v){
		std::cout << "element: "<< i << '\n';
	}

	for (auto it=begin(v); it!=end(v);++it){
		std::cout << (*it)++ << ", ";
	}
	std::cout << '\n';
	for (auto it=cbegin(v); it!=cend(v);++it){
		std::cout << *it << ", ";
	}
}

