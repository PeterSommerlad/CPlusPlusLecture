#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
int main() {
	std::vector<int> const cv{1,2,3,5,7,11};
	using std::cout;
	std::ostream_iterator<int> out{cout,", "};
	cout << "low primes\n";
	copy(begin(cv),end(cv),out);
	cout << "\nin reverse order:\n";
	copy(rbegin(cv),rend(cv),out);
	std::vector<int> v{cv}; // copies values
	cout << "\nlow primes copied reverse\n";
	copy(cbegin(v),cend(v),out);
	cout << "\nv is "<< (v.empty()?"":"not ")<<"empty\n";
	cout << "its size is "<<v.size();
	v.clear();
	cout << "\nv is "<< (v.empty()?"":"not ")<<"empty\n";
	v.assign(begin(cv),end(cv)); // use a range
	cout << "\nlow primes again\n";
	copy(cbegin(v),cend(v),out);
}

