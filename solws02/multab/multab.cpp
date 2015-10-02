#include <iostream>
void printnice(std::ostream &out,unsigned const i){
	std::cout.width(5);
	std::cout << i;
}

void printheader(std::ostream &out,unsigned const limit) {
	printnice(out, 0);
	for (unsigned j = 1; j <= limit; ++j) {
		printnice(out, j);
	}
	out << '\n';
}
unsigned enterlimit(std::istream& in, std::ostream &out){
	unsigned limit{};
	while (in.good() && (limit < 1 || limit > 30)){
		out << "enter limit (max 30):";
		in >> limit;
	}
	return limit<1||limit>30?20:limit;
}

int main() {
	auto const limit = enterlimit(std::cin, std::cout);
	printheader(std::cout, limit);
	for (unsigned i = 1; i <= limit; ++i) {
		printnice(std::cout, i);
		for (auto j = 1u; j <= limit; ++j) {
			printnice(std::cout, i * j);
		}
		std::cout << '\n';
	}
}
