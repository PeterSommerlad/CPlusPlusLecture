#include <iostream>
#include <vector>
#include <iomanip>
#include <iterator>
#include <algorithm>

std::string to_string_width5(unsigned num) {
	std::ostringstream os { };
	os << std::setw(5) << num;
	return os.str();
}

int main(){
	std::vector<unsigned> v(20);
	iota(begin(v),end(v),1);
	std::ostream_iterator<std::string> out{std::cout,""};
	for_each(cbegin(v),cend(v),[=](unsigned row){
		transform(cbegin(v),cend(v),out,
				[=](unsigned col){
					return to_string_width5(col* row);
				});
		std::cout << '\n';
	});
}
