#include <iostream>

void printCommaSeparated(std::ostream& out){out << '\n';} // base case

template <typename HEAD, typename... TAIL>
void printCommaSeparated(std::ostream &out,HEAD const &head, TAIL const &... tail){
	out << head;
	if (sizeof...(tail))
		out << ", ";
	printCommaSeparated(out,tail...);
}
int main() {
	printCommaSeparated(std::cout,"A simple demo ", 0x0f, "typesaf",'e',"output");
}
