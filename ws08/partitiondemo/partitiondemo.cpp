#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
template<typename PRED>
void show(std::ostream &os,
		  std::vector<int> const& v,
		  PRED const& pred) {
	std::ostream_iterator<int> out(os, ", ");
	copy(v.begin(), v.end(), out);
	os << std::boolalpha
	<< is_partitioned(v.begin(), v.end(), pred) << '\n';
}
int main() {
	std::vector<int> v{3,1,4,1,5,9,2,6};
	auto greater4=[](int x){return x>4;};
	using std::cout;
	show(cout,v, greater4);
	partition(v.begin(), v.end(), greater4);
	show(cout,v,greater4);
	auto it=partition_point(v.begin(),v.end(),greater4);
	cout<<"partition point index "<< distance(v.begin(),it);
}
