#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"


// base case overload
void println(std::ostream &out) {
	out << "\n";
}
//variadic template
template<typename Head, typename... Tail>
void println(std::ostream &out, Head const& head, Tail const& ...tail) {
	out << head;
	if (sizeof...(tail)) {
		out << ", ";
	}
	println(out,tail...); //recurse on tail
}

template <typename... ARGS>
void variadic(ARGS... args){
	println(std::cout,args...);
}



void testVariadicPrint(){
	std::ostringstream out{};
	println(out,1,2,3,"hello",' ',"world");
	ASSERT_EQUAL("1, 2, 3, hello,  , world\n",out.str());
}
void showVariadic(){
	variadic(1,2,3);
	variadic();
	variadic("eins",2,3.0);
	ASSERTM("dummy assert", true);
}


void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testVariadicPrint));
	s.push_back(CUTE(showVariadic));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}




