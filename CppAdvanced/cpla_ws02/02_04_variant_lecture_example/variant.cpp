#include <variant>
#include <iostream>
#include <string>

struct VariantHandler {
	void operator()(int & i) const {
		std::cout << "int: " << i << '\n';
	}
	void operator()(float & f) const {
		std::cout << "float: " << f << '\n';
	}
	void operator()(std::string & s) const {
		std::cout << "string: " << s << '\n';
	}
};

void variant_example(std::ostream & out) {
	std::variant<int, float, std::string> value{};
	out << std::get<int>(value) << '\n';

	value = "char const [15]";
	try {
		out << std::get<int>(value) << '\n';
	} catch(std::bad_variant_access const &) {
		out << "std::bad_any_cast thrown, "
		       "when accessing string as int!\n";
	}

	value = 15.0f;
	std::visit(VariantHandler{}, value);

	//value = 10L; //Compile error
}


void variant_compare() {
	std::variant<int, float> vIF{}, vIF_too{};
	std::variant<float, int> vFI{};
	vIF == vIF_too;
	//vIF == vFI; //Compile error
}

int main() {
  variant_example(std::cout);
}


