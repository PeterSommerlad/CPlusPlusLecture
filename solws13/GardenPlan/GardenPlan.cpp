#include "Shapes.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <vector>

using namespace std;
using namespace Gardening;

using ShapePtr = shared_ptr<Shape>;
using GardenPlan = vector<ShapePtr>;

namespace Gardening {
ostream & operator<<(ostream & out, ShapePtr const & shape) {
	shape->print(out);
	return out;
}
}

void printPlan(GardenPlan const & plan, ostream & out){
	copy(plan.begin(), plan.end(), ostream_iterator<ShapePtr>{out, "\n"});
}

template<typename F>
auto mapReduce(GardenPlan const & plan, F const & function) {
	return accumulate(plan.begin(), plan.end(), 0, [&function](auto lhs, auto rhs) {
		return lhs + function(rhs);
	});
}

int main() {
	GardenPlan plan {
		make_shared<Triangle>(3, 6, 6.70820393),
		make_shared<Triangle>(3, 4, 4),
		make_shared<Triangle>(3, 4, 4),
		make_shared<Diamond>(4, 60),
		make_shared<Square>(3),
		make_shared<Square>(3),
		make_shared<Rectangle>(4, 9),
		make_shared<Circle>(4),
		make_shared<Ellipse>(5, 3)
	};
	printPlan(plan, cout);

	auto const accessShape = [](ShapePtr const shape) {return shape->pegs();};
	cout << "pegs needed: " << mapReduce(plan, accessShape) << '\n';

	auto const accessSeeds = [](ShapePtr const shape) {return shape->seeds();};
	cout << "seeds needed: " << mapReduce(plan, accessSeeds) <<" kg\n";

	auto const accessRope = [](ShapePtr const shape) {return shape->ropes();};
	cout << "rope needed: " << mapReduce(plan, accessRope) << " m\n";
}


