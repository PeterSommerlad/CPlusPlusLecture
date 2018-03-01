#include <any>
#include <iostream>

void any_example(std::ostream & out) {
	std::any value{};
	out << "has value? " << value.has_value() << '\n';
	value = 5;
	out << std::any_cast<int>(value) << '\n';
	try {
		std::any_cast<long>(value);
	} catch(std::bad_any_cast const &) {
		out << "std::bad_any_cast thrown, "
		       "when accessing int as long!\n";
	}
}

int main() {
  any_example(std::cout);
}


