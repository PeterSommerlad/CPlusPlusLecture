#include <iostream>
#include <stack>

#include <memory>

struct Point {
	Point(int x, int y) :
			x { x }, y { y } {
		std::cout << "creating Point{" << x << ", " << y << "}\n";
	}
	int const x, y;
	~Point() {
		std::cout << "destroying Point{" << x << ", " << y << "}\n";
	}
	Point(Point const &) = delete;
	Point(Point&&) = delete;
};

int main(int argc, char **argv) {
	std::stack<Point> pointStack{};
	pointStack.emplace(1, 2);
}
