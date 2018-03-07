#include <iostream>

decltype(auto) f1() {
  int x = 23;
  return (x); // returning reference to local variable
}

int main(int argc, char **argv) {

	std::cout << f1() << std::endl; // undefined behavior
}
