#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "SquareSuite.h"
#include "TriangleSuite.h"
#include "DiamondSuite.h"
#include "RectangleSuite.h"
#include "CircleSuite.h"
#include "EllipseSuite.h"
#include "PolymorphismSuite.h"


void runSuite(int argc, char** argv){
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	auto runner = cute::makeRunner(lis);

	cute::suite squareSuite = make_suite_SquareSuite();
	runner(squareSuite, "Square Suite");
	cute::suite triangleSuite = make_suite_TriangleSuite();
    runner(triangleSuite, "Triangle Suite");
    cute::suite diamondSuite = make_suite_DiamondSuite();
    runner(diamondSuite, "Diamond Suite");
    cute::suite rectangleSuite = make_suite_RectangleSuite();
    runner(rectangleSuite, "Rectangle Suite");
    cute::suite circleSuite = make_suite_CircleSuite();
    runner(circleSuite, "Circle Suite");
    cute::suite ellipseSuite = make_suite_EllipseSuite();
    runner(ellipseSuite, "Ellipse Suite");
    cute::suite polymorphismSuite = make_suite_PolymorphismSuite();
    runner(polymorphismSuite, "Polymorphism Suite");
}


int main(int argc, char **argv) {
	runSuite(argc, argv);
}
