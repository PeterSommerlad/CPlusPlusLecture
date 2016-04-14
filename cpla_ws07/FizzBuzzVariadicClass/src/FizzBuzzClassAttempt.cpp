#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

template <size_t ...nums>
struct FizzBuzz;

template <>
struct FizzBuzz<>{
	FizzBuzz(std::ostream&out):os{out}{}
	virtual ~FizzBuzz(){}
protected:
	std::ostream& os;
};
template <size_t n,size_t ...rest>
struct FizzBuzz<n,rest...>:FizzBuzz<rest...> {

	FizzBuzz(std::ostream &out):FizzBuzz<rest...>{out}{}
	~FizzBuzz(){
		this->os << n ;
	}
};
template <size_t ...rest>
struct FizzBuzz<3,rest...>:FizzBuzz<rest...> {

	FizzBuzz(std::ostream &out):FizzBuzz<rest...>{out}{}
	~FizzBuzz(){
		this->os << "Fizz" ;
	}
};
template <size_t ...rest>
struct FizzBuzz<5,rest...>:FizzBuzz<rest...> {

	FizzBuzz(std::ostream &out):FizzBuzz<rest...>{out}{}
	~FizzBuzz(){
		this->os << "Buzz" ;
	}
};



void testFizzBuzzSequenceUpTo16() {
	std::ostringstream out;
	{
	FizzBuzz<> fb0(out);
	}
	ASSERT_EQUAL("",out.str());
}
void fizzBuzzSingle1() {
	std::ostringstream out;
	{
	FizzBuzz<1> fb(out);
	}
	ASSERT_EQUAL("1",out.str());
}
void FizzBuzzSingleFizz(){
	std::ostringstream out;
	{
	FizzBuzz<3> fb(out);
	}
	ASSERT_EQUAL("Fizz",out.str());

}
void FizzBuzzSingleBuzz(){
	std::ostringstream out;
	{
	FizzBuzz<5> fb(out);
	}
	ASSERT_EQUAL("Buzz",out.str());
}
void FizzBuzzSequenceToBuzz(){
	std::ostringstream out;
	{
	FizzBuzz<1,2,3,4,5> fb(out);
	}
	ASSERT_EQUAL("12Fizz4Buzz",out.str());
}


void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testFizzBuzzSequenceUpTo16));
	s.push_back(CUTE(fizzBuzzSingle1));
	s.push_back(CUTE(FizzBuzzSingleFizz));
	s.push_back(CUTE(FizzBuzzSingleBuzz));
	s.push_back(CUTE(FizzBuzzSequenceToBuzz));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



