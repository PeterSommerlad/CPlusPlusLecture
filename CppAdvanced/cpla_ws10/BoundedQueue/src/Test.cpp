#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "bounded_queue_signatures_suite.h"
#include "bounded_queue_default_behavior_suite.h"
#include "bounded_queue_content_suite.h"
#include "bounded_queue_semantic_suite.h"
#include "bounded_queue_student_suite.h"
#include "bounded_queue_heap_memory_suite.h"
#include "bounded_queue_non_default_constructible_element_type_suite.h"
#include "bounded_queue_single_threaded_lock_suite.h"
#include "bounded_queue_multi_threaded_suite.h"


void runAllTests(int argc, char const *argv[]){
	//TODO add your test here
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_queue_signatures_suite(), "BoundedQueue API Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_queue_default_behavior_suite(), "BoundedQueue Default Behavior Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_queue_content_suite(), "BoundedQueue Content Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_queue_semantic_suite(), "BoundedQueue Semantic Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_queue_student_suite(), "BoundedQueue Student Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_queue_heap_memory_suite(), "BoundedQueue Heap Memory Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_queue_non_default_constructible_element_type_suite(), "BoundedQueue Non-Default-Constructible Element Type Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_queue_single_threaded_lock_suite(), "BoundedQueue Single Threaded Lock Tests");
	cute::makeRunner(lis,argc,argv)(make_suite_bounded_queue_multi_threaded_suite(), "BoundedQueue Multi-Threaded Tests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



