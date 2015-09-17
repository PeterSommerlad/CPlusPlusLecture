#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>
#include <cstdlib>
size_t count_blanks(std::string s){
	size_t count{0};
	for (size_t i=0; i < s.size(); ++i)
		if (s[i] == ' ') ++count;
	return count;
}

void copydemo(std::vector<int> v) {
	using out= std::ostream_iterator<int>;
	copy(begin(v), end(v),out{ std::cout,", " });
	v.push_back(42);
	copy(begin(v), begin(v) + 2, back_inserter(v));
	std::cout <<'\n';
	copy(begin(v), end(v),out{ std::cout,", " });
}

void print(int x){
	std::cout << "print:"<< x++ << '\n';
}

void for_each_demo(){
	std::vector<int> v{5,4,3,2,1};
	std::cout << std::accumulate(begin(v),end(v),0)<< " = sum\n";

	for_each(begin(v),end(v),[](auto x){
		std::cout << x++ << '\n';});
	for_each(crbegin(v),crend(v),print);

	copydemo(v);
}

void generate_find_demo(){
	std::vector<int> v{};
	srand(time(0));
	generate_n(back_inserter(v),100,[]{return rand()%100;});
	auto zero_it=find(begin(v),end(v),0);
	if (zero_it == end(v)){
		std::cout << "\nno zero found \n";
	} else {
		std::cout << "\nfound zero at position:"
				<< distance(begin(v),zero_it)<<'\n';
	}
	auto odd=find_if(begin(v),end(v),[](auto x){return x%2;});
	if (odd == end(v)){
		std::cout << "no odd number found\n";
	} else {
		std::cout << "found odd number:" << *odd
				<< "\nat position:"<<distance(begin(v),odd)<< '\n';
	}
	std::cout << count(begin(v),end(v),42)<<" times 42\n";
	std::cout << count_if(begin(v),end(v),
			[](auto x){return 0==(x%2);})<<" even numbers\n";
}

int main(){
	std::string s{"A journey of a thousand miles begins with a single step"};
	std::cout << count(s.begin(),s.end(),' ') << " blanks\n";
	std::cout << "distance: "<< distance(s.begin(),s.end()) <<'\n';
	std::cout << "in a string of length: "<< s.size()<<'\n';
	std::cout << count_blanks(s) << " blanks\n";

	for_each_demo();
	generate_find_demo();
}

