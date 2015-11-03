#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>
#include <list>
#include <deque>

template<typename ITER>
void print(std::ostream &out, ITER b, ITER e) {
	using oi=std::ostream_iterator<int>;
	copy(b, e, oi { out, ", " });
	out << '\n';
}

void demoArray() {
	std::array<int, 6> a { { 1, 1, 2, 3, 5, 8 } };
	print(std::cout, cbegin(a), cend(a));
	a.fill(42); // all values are 42
	a.at(2) = 0;
	a[4] = 1;
	print(std::cout, cbegin(a), cend(a));
}

void demoList() {
	std::list<int> l { 3, 5, 1, 2, 8, 1 };
	print(std::cout, cbegin(l), cend(l));
	l.sort();
	print(std::cout, cbegin(l), cend(l));
	l.unique();
	print(std::cout, cbegin(l), cend(l));
	std::list<int> l4_42s(4, 42);
	auto it = find(cbegin(l), cend(l), 2);
	l.splice(it, l4_42s);
	print(std::cout, cbegin(l), cend(l));
	std::cout << "spliced from size: " << l4_42s.size();
}

void demoFeatures() {
	std::vector<int> v { 1, 2, 3, 5, 7, 11 };
	std::vector<int> vv { v };
	if (v == vv)
		v.clear();
	std::list<int> l(5, 1);
	std::deque<int> q { cbegin(v), cend(v) };
	q.push_front(42);
	q.pop_back();
	v.clear();
}
int main() {
	demoArray();
	demoList();

}
