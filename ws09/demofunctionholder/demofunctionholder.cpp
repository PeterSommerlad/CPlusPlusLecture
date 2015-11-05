#include <functional>
#include <iostream>

void apply_and_print(std::ostream& out,
		std::function<bool(int)> apredicate) {
	if (apredicate) { // implicit bool conversion
		out << "pred(42) is " << apredicate(42) << '\n';
	} else {
		out << "empty function holder\n";
	}
}

int main(){
	using std::cout;
	cout << std::boolalpha;
	std::function<bool(int)> apredicate { };
	apply_and_print(cout,apredicate);
	apredicate = [](int i){return i%2;};
	apply_and_print(cout,apredicate);
	apredicate = std::not1(apredicate);
	apply_and_print(cout,apredicate);
	apredicate = nullptr;
	apply_and_print(cout,apredicate);
}
