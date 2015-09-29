#include <iostream>
#include <cstdlib> // srand, rand, time functions
#include <stdexcept>
void mightthrow_logic_error(){
	if (rand()%2) throw std::logic_error{"logic"};
}
void must_be_called_with_greater_3(unsigned i){
	if (i <= 3) throw std::invalid_argument{"too small"};
}
int main() try {
	srand(time(0)); // randomize rand()
	mightthrow_logic_error();
	must_be_called_with_greater_3(rand()%6);
	if (rand()%2) throw std::string{"error"};
	if (rand()%2) throw 15;
	throw "hallo";
} catch (std::logic_error const &e) {
	std::cout << "logic error: \'" << e.what() << "\'\n";
	throw; // re-throw the caught exception
} catch (std::exception const &e) {
	std::cout << "exception: \'" << e.what() << "\'\n";
} catch (int const &i) {
	std::cout << "exception int: <" << i << ">\n";
} catch (std::string const &s) {
	std::cout << "exception string: \"" << s << "\"\n";
} catch (...) {
	std::cout << "unknown exception value\n";
}
