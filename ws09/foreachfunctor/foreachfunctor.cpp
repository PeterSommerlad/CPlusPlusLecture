#include <iostream>
#include <algorithm>
#include <vector>






struct averager {
	void operator()(double d) {
		accumulator += d;
		++counter;
	}
	double sum() const { return accumulator; }
	double count() const { return counter; }
	double average() const { return sum()/count(); }
private:
	double accumulator{};
	unsigned counter{};
};








int main(){
	std::vector<double> v{7,4,1,3,5,3.3,4.7};
	auto const res=for_each(v.begin(),v.end(),averager{});
	std::cout << "sum = " << res.sum() << '\n'
			  << "count = " << res.count() << '\n'
			  << "average = "<< res.average() << '\n';
}
