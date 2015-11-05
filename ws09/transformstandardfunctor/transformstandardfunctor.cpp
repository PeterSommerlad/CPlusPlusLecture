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


void demotransform(std::ostream& out){
	std::vector<int> v{-1,2,-5,3,-4,-2};
	print(v,out);
	transform(v.begin(),v.end(),
			  v.begin(),[](int x){return -x;});
	print(v,out);
	transform(v.begin(),v.end(),
			  v.begin(),std::negate<int>{});
	print(v,out);
	transform(v.begin(),v.end(),v.begin(),
			  v.begin(),std::multiplies<int>{});
	print(v,out);

}




int main(){
	demotransform(std::cout);
}












