#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>




void print(std::vector<int> v, std::ostream& out){
	std::ostream_iterator<int> os{out,", "};
	copy(v.begin(),v.end(),os);
	out << '\n';
}


void demosort(std::ostream &out){
	std::vector<int> v{-1,2,-5,3,-4,-2};
	print(v,out);
	sort(v.begin(),v.end(),std::greater<>{});
	print(v,out);
}




int main(){
	demosort(std::cout);
}












