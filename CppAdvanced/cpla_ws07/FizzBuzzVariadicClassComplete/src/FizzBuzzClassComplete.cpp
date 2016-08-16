#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <utility>
template <size_t ...nums>
struct FizzBuzz;

template <>
struct FizzBuzz<>{
	FizzBuzz(std::ostream&out):os{out}{}
	virtual ~FizzBuzz(){}
protected:
	std::ostream& os;
};


template <size_t n,typename=void>
struct FizzBuzzSingle{
	FizzBuzzSingle(std::ostream &out):os{out}{}
	~FizzBuzzSingle(){ this->os << n <<'\n'; }
private:
	std::ostream& os;
};

template <size_t n>
struct FizzBuzzSingle<n,typename std::enable_if<n%3==0&&n%5>::type >{
	FizzBuzzSingle(std::ostream &out):os{out}{}
	~FizzBuzzSingle(){
		this->os << "Fizz\n";
	}
private:
	std::ostream& os;
};
template <size_t n>
struct FizzBuzzSingle<n, std::enable_if_t<n%3&&n%5==0>>{
	FizzBuzzSingle(std::ostream &out):os{out}{}
	~FizzBuzzSingle(){
		this->os << "Buzz\n";
	}
private:
	std::ostream& os;
};

template <size_t n>
struct FizzBuzzSingle<n,std::enable_if_t<n%3==0&&n%5==0>>{
	FizzBuzzSingle(std::ostream &out):os{out}{}
	~FizzBuzzSingle(){
		this->os << "FizzBuzz\n";
	}
private:
	std::ostream& os;
};


template <size_t n,size_t ...rest>
struct FizzBuzz<n,rest...>:FizzBuzz<rest...>,FizzBuzzSingle<n> {

	FizzBuzz(std::ostream &out):FizzBuzz<rest...>{out}, FizzBuzzSingle<n>{out}{}
};
template <size_t ...rest>
struct FizzBuzz<0,rest...>:FizzBuzz<rest...> {

	FizzBuzz(std::ostream &out):FizzBuzz<rest...>{out}{}
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
	ASSERT_EQUAL("1\n",out.str());
}
void FizzBuzzSingleFizz(){
	std::ostringstream out;
	{
	FizzBuzz<3> fb(out);
	}
	ASSERT_EQUAL("Fizz\n",out.str());

}
void FizzBuzzSingleBuzz(){
	std::ostringstream out;
	{
	FizzBuzz<5> fb(out);
	}
	ASSERT_EQUAL("Buzz\n",out.str());
}
void FizzBuzzSequenceToBuzz(){
	std::ostringstream out;
	{
	FizzBuzz<1,2,3,4,5> fb(out);
	}
	ASSERT_EQUAL(
R"(1
2
Fizz
4
Buzz
)",out.str());
}
template<size_t ...nums>
auto makeFizzBuzz(std::ostream &out,std::index_sequence<nums...>){
	return FizzBuzz<nums...>{out};
}
void FizzBuzzSequenceToFizzBuzzAndBeyond(){
	std::ostringstream out;
	{FizzBuzz<> fb=makeFizzBuzz(out,std::make_index_sequence<21>());}
	ASSERT_EQUAL(
R"(1
2
Fizz
4
Buzz
Fizz
7
8
Fizz
Buzz
11
Fizz
13
14
FizzBuzz
16
17
Fizz
19
Buzz
)",out.str());
}





void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testFizzBuzzSequenceUpTo16));
	s.push_back(CUTE(fizzBuzzSingle1));
	s.push_back(CUTE(FizzBuzzSingleFizz));
	s.push_back(CUTE(FizzBuzzSingleBuzz));
	s.push_back(CUTE(FizzBuzzSequenceToBuzz));
	s.push_back(CUTE(FizzBuzzSequenceToFizzBuzzAndBeyond));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



