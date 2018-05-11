#include <iostream>

struct Shape {
  virtual unsigned area() const = 0;
  virtual ~Shape() {}
};

struct Square : Shape {
  Square(unsigned side_length)
    : side_length{side_length} {}
  unsigned area() const {
    return side_length * side_length;
  }
  unsigned const side_length;
};

int main(int argc, char **argv) {
	//1 for non-virtual (empty) Shape
	//4 or 8 for virtual (empty) Shape
	std::cout << sizeof(Shape) << '\n';

	//4 or 8 for non-virtual Square
	//8 to 16 for virtual Square
	std::cout << sizeof(Square) << '\n';
}
