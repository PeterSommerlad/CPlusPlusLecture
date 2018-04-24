#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "bounded_buffer_signatures_suite.h"
#include "bounded_buffer_default_behavior_suite.h"
#include "bounded_buffer_content_suite.h"
#include "bounded_buffer_content_suite_no_default.h"
#include "bounded_buffer_semantic_suite.h"
#include "bounded_buffer_semantic_suite_no_default.h"
#include "bounded_buffer_student_suite.h"


void runAllTests(int argc, char const *argv[]) {
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_buffer_signatures_suite(), "BoundedBuffer Signature Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_buffer_default_behavior_suite(), "BoundedBuffer Default Behavior Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_buffer_content_suite(), "BoundedBuffer Content Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_buffer_content_suite_no_default(), "BoundedBuffer Content Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_buffer_semantic_suite(), "BoundedBuffer Semantic Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_buffer_semantic_suite_no_default(), "BoundedBuffer Semantic Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_buffer_student_suite(), "BoundedBuffer Student Tests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

