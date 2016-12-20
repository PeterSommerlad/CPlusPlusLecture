#include "BedFactory.h"
#include "Shape.h"
#include "shoppinglist.h"
#include "Square.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Diamond.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include <stdexcept>
#include <cmath>
void createSquare() {
	Square sq{5};
	ASSERT_EQUAL(4, sq.pegs());
	ASSERT_EQUAL(2.5, sq.seeds());
	ASSERT_EQUAL(20,sq.rope());
}
void invalidSquare(){
	ASSERT_THROWS(Square{0},std::logic_error);
}


void createRectangle(){
	Rectangle r{3,4};
	ASSERT_EQUAL(4,r.pegs());
	ASSERT_EQUAL(1.2, r.seeds());
	ASSERT_EQUAL(14.0,r.rope());
}
void invalidRectangle(){
	ASSERT_THROWS((Rectangle{0,10}),std::logic_error);
}
void createTriangle(){
	Triangle t{4,3,3};
	ASSERT_EQUAL(3,t.pegs());
	ASSERT_EQUAL(0.1*2*sqrt(5.0),t.seeds());
	ASSERT_EQUAL(10.0,t.rope());
}
void invalidTriangle(){
	ASSERT_THROWS((Triangle{1,1,10}),std::logic_error);
}

void createDiamond(){
	Diamond d{4,4,60};
	ASSERT_EQUAL(4,d.pegs());
	ASSERT_EQUAL(16,d.rope());
	double const PI = 4 * atan(1.0);
	ASSERT_EQUAL(4 * sin(60.0/180*PI)*4*0.1,d.seeds());
}
void invalidDiamond(){
	ASSERT_THROWS((Diamond{1,1,190}),std::logic_error);
}


void printTriangle(){
	Triangle t{3,4,5};
	ASSERT_EQUAL("Triangle",t.name());
	std::ostringstream os;
	os << t;
	ASSERT_EQUAL("Triangle 3 12 0.6\n",os.str());
}

void factoryDiamond(){
	std::istringstream in("Diamond 4 4 60");
	ShapePtr d=makeBed(in);
	ASSERT_EQUAL(4,d->pegs());
	ASSERT_EQUAL(16,d->rope());
	double const PI = 4 * atan(1.0);
	ASSERT_EQUAL(4 * sin(60.0/180*PI)*4*0.1,d->seeds());
}
void factoryAll(){
	std::istringstream in("Diamond 4 4 60\n"
						  "Rectangle 3 4\n"
						  "Square 5\n"
						  "Triangle 4 3 3\n");
	auto d=makeBed(in);
	ASSERT_EQUAL(4,d->pegs());
	ASSERT_EQUAL(16,d->rope());
	double const PI = 4 * atan(1.0);
	ASSERT_EQUAL(4 * sin(60.0/180*PI)*4*0.1,d->seeds());
	auto r=makeBed(in);
	ASSERT_EQUAL(4,r->pegs());
	ASSERT_EQUAL(1.2, r->seeds());
	ASSERT_EQUAL(14.0,r->rope());
	auto sq=makeBed(in);
	ASSERT_EQUAL(4, sq->pegs());
	ASSERT_EQUAL(2.5, sq->seeds());
	ASSERT_EQUAL(20,sq->rope());
	auto t=makeBed(in);
	ASSERT_EQUAL(3,t->pegs());
	ASSERT_EQUAL(0.1*2*sqrt(5.0),t->seeds());
	ASSERT_EQUAL(10.0,t->rope());
	ASSERT_THROWS(makeBed(in),std::logic_error);
}

void readAllShapes(){
	std::istringstream in("Diamond 4 4 60\n"
						  "Rectangle 3 4\n"
						  "Square 5\n"
						  "Triangle 4 3 3\n");
	auto v=createAllBeds(in);
	ASSERT_EQUAL(4,v.size());
}
void shoppingList(){
	std::istringstream in("Diamond 4 4 60\n"
						  "Rectangle 3 4\n"
						  "Square 5\n"
						  "Triangle 4 3 3\n");
	std::ostringstream out{};
	printShoppingList(createAllBeds(in),out);
	ASSERT_EQUAL("Diamond 4 16 1.38564\n"
"Rectangle 4 14 1.2\n"
"Square 4 20 2.5\n"
"Triangle 3 10 0.447214\n"
"pegs needed: 15\n"
"seeds needed: 5.53285 kg\n"
"rope needed: 60 m\n",out.str());
}




void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(createSquare));
	s.push_back(CUTE(createRectangle));
	s.push_back(CUTE(createTriangle));
	s.push_back(CUTE(createDiamond));
	s.push_back(CUTE(printTriangle));
	s.push_back(CUTE(factoryDiamond));
	s.push_back(CUTE(invalidTriangle));
	s.push_back(CUTE(invalidSquare));
	s.push_back(CUTE(invalidDiamond));
	s.push_back(CUTE(invalidRectangle));
	s.push_back(CUTE(factoryAll));
	s.push_back(CUTE(readAllShapes));
	s.push_back(CUTE(shoppingList));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
}



