/*
 * MIT License

Copyright (c) 2016/2017 Peter Sommerlad

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#include "scope_exit.h"
#include "unique_resource.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <fstream>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

#include <string>

#include <sstream>

#include <functional>

#include <ostream>

//#define CHECK_COMPILE_ERRORS

using std::experimental::unique_resource;
using std::experimental::make_unique_resource_checked;
using std::experimental::scope_exit;
using std::experimental::scope_fail;
using std::experimental::scope_success;

void testPtrPairThrowingCtor() {
	std::ostringstream out { };
	{
		auto guard = scope_exit([&] {out << "done\n";});
	}
	ASSERT_EQUAL("done\n", out.str());
}

void testScopeExitWithCPP17DeducingCtors() {
	std::ostringstream out { };
	{
		scope_exit guard([&] {out << "done\n";});
	}
	ASSERT_EQUAL("done\n", out.str());
}
void testScopeFailWithCPP17DeducingCtors(){
	std::ostringstream out { };
	{
		scope_fail guard([&] {out << "not done\n";});
	}
	ASSERT_EQUAL("",out.str());
	try {
		scope_fail guard([&] {out << "done\n";});
		throw 0;
	} catch (const int) {
	}
	ASSERT_EQUAL("done\n", out.str());
}
void testScopeSuccessWithCPP17DeducingCtors(){
	std::ostringstream out { };
	{
		scope_success guard([&] {out << "done\n";});
	}
	ASSERT_EQUAL("done\n", out.str());
	try {
		scope_success guard([&] {out << "not done\n";});
		throw 0;
	} catch(int){}
	ASSERT_EQUAL("done\n", out.str());
}


void testDismissedGuard() {
	std::ostringstream out { };
	{
		auto guard = scope_exit([&] {out << "done1\n";});
		auto guard2dismiss = scope_exit([&] {out << "done2\n";});
		guard2dismiss.release();
	}
	ASSERT_EQUAL("done1\n", out.str());
}
void testThrowDoesntCrashIt() { // LEWG wants it to crash!
	std::ostringstream out { };
	{
		auto guard = scope_exit([&] {out << "done\n";});
		auto guard1 = scope_exit([] {throw 42;});
		guard1.release(); // we no longer want throwing scope guards
	}
	ASSERT_EQUAL("done\n", out.str());

}
void testScopeExitWithReferenceWrapper(){
	std::ostringstream out { };
	const auto &lambda = [&] {out << "lambda done.\n";};
	{
		auto guard=scope_exit(std::cref(lambda));
	}
	ASSERT_EQUAL("lambda done.\n",out.str());
}
struct non_assignable_resource{
	non_assignable_resource()=default;
	non_assignable_resource(int){}
	void operator=(const non_assignable_resource &) = delete;
	non_assignable_resource& operator=(non_assignable_resource  &&) noexcept(false){ throw "buh";};
	non_assignable_resource(non_assignable_resource  &&) =default;
};
void testscopeExitWithNonAssignableResourceAndReset(){
	std::ostringstream out { };
	const auto &lambda = [&](auto &&) {out << "lambda done.\n";};
	{
		auto guard=unique_resource(non_assignable_resource{},std::cref(lambda));
		//guard.reset(2);//throws... need to figure out, what I wanted to trigger here. AH, compile error?
	}
	ASSERT_EQUAL("lambda done.\n",out.str());
}



// by Eric Niebler, adapted for unit testing
struct throwing_copy
{
	throwing_copy(const char* sz, std::ostream &os) :
			sz_ { sz }, out { os } {
	}
	throwing_copy(const throwing_copy &other) :
			out { other.out }
    {
    		using namespace std::literals;
        throw "throwing_copy copy attempt:"s+sz_;
    }
    void operator()() const
    {
        out << sz_ << std::endl;
    }
    template <typename RES>
    void operator()(RES const &res) const
    {
        out << sz_ << res<< std::endl;
    }

    bool operator==(int i)const &{
    		return i==0;
    }
    friend std::ostream& operator<<(std::ostream &os,throwing_copy const &t){
    		return os << t.sz_ ;
    }
private:
	const char *sz_ { "" };
    std::ostream &out;
};



void testsFromEricNiebler_scope_exit_with_throwing_function_object(){
	std::ostringstream out { };
	try
	    {
	        throwing_copy c{"called anyway",out};
	        auto &&x = scope_exit(c);
	        out << "whoops" << std::endl;
	    }
	    catch(...)
	    {
	    		out << "expected";
	    }
	ASSERT_EQUAL("called anyway\nexpected", out.str());
}

void testsFromEricNiebler_scope_success_with_throwing_function_object(){
	std::ostringstream out { };
	try
	    {
        throwing_copy c{"Oh noes!!!",out};
        auto &&x = scope_success(c);
	        out << "whoops" << std::endl;
	    }
	    catch(...)
	    {
	    	out << "just exception\n";
	    }
	ASSERT_EQUAL("just exception\n", out.str());
}

void testsFromEricNiebler_scope_fail_with_throwing_function_object(){
	std::ostringstream out { };
	try
	    {
        throwing_copy c{"called because of exception!!!",out};
        auto &&x = scope_fail(c);
	        out << "whoops" << std::endl;
	    }
	    catch(...)
	    {
	    		out << "expected";
	    }
	ASSERT_EQUAL("called because of exception!!!\nexpected", out.str());
}


void testThrowOnUniqueResourceDoesntCrashIt() {
	std::ostringstream out { };
	{
		auto guard = unique_resource(1, [&] (auto) {out << "done\n";});
		// we do no longer allow that for unique_resource
//		try {
//			{
//				auto guard1 = unique_resource(2, [] (auto) noexcept(false) {throw 42;});
//				guard1.reset();
//			}
//			FAILM("didn't throw");
//		} catch (int) {
//		} catch (...) {
//			FAILM("threw unknown error");
//		}
	}
	ASSERT_EQUAL("done\n", out.str());

}

void testUniqueResourceSimple() {
	using namespace std;
	std::ostringstream out { };

	const std::string msg { " deleted resource\n" };
	{
		auto res = unique_resource(std::ref(msg), [&out](string msg) {out << msg<<flush;});
	}
	ASSERT_EQUAL(msg, out.str());
}
void testUniqueResourceByReference() {
	using namespace std;
	std::ostringstream out { };

	const std::string msg { " deleted resource\n" };
	{
		auto res = unique_resource<std::string const &
				,std::function<void(string)>>(msg, [&out](string msg) {out << msg<< flush;});
	}
	ASSERT_EQUAL(msg, out.str());
}

void test_unique_resource_semantics_reset() {
	std::ostringstream out { };
	{
		auto cleanup = unique_resource(1, [&out](int i) {out << "cleaned " << i;});
		cleanup.reset(2);
	}
	ASSERT_EQUAL("cleaned 1cleaned 2", out.str());
}

void demonstrate_unique_resource_with_stdio() {
	const std::string filename = "hello.txt";
	auto fclose=[](auto fptr){::fclose(fptr);};
	{
		auto file = unique_resource(::fopen(filename.c_str(), "w"), fclose);
		::fputs("Hello World!\n", file.get());
		ASSERT(file.get()!= NULL);
	}
	{
		std::ifstream input { filename };
		std::string line { };
		getline(input, line);
		ASSERT_EQUAL("Hello World!", line);
		getline(input, line);
		ASSERT(input.eof());
	}
	::unlink(filename.c_str());
	{
		auto file = make_unique_resource_checked(::fopen("nonexistentfile.txt", "r"), nullptr, fclose);
		ASSERT_EQUAL((FILE*)NULL, file.get());
	}

}
void demonstrate_unique_resource_with_stdio_Cpp17() {
	const std::string filename = "hello.txt";
	auto fclose=[](auto fptr){::fclose(fptr);};

	{
		unique_resource file(::fopen(filename.c_str(), "w"), fclose);
		::fputs("Hello World!\n", file.get());
		ASSERT(file.get()!= NULL);
	}
	{
		std::ifstream input { filename };
		std::string line { };
		getline(input, line);
		ASSERT_EQUAL("Hello World!", line);
		getline(input, line);
		ASSERT(input.eof());
	}
	::unlink(filename.c_str());
	{
		auto file = make_unique_resource_checked(::fopen("nonexistentfile.txt", "r"), nullptr, fclose);
		ASSERT_EQUAL((FILE*)NULL, file.get());
	}

}

void demontrate_unique_resource_with_POSIX_IO() {
	const std::string filename = "./hello1.txt";
	auto close=[](auto fd){::close(fd);};
	{
		auto file = unique_resource(::open(filename.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0666), close);

		::write(file.get(), "Hello World!\n", 12u);
		ASSERT(file.get() != -1);
	}
	{
		std::ifstream input { filename };
		std::string line { };
		getline(input, line);
		ASSERT_EQUAL("Hello World!", line);
		getline(input, line);
		ASSERT(input.eof());
	}
	::unlink(filename.c_str());
	{
		auto file = make_unique_resource_checked(::open("nonexistingfile.txt", O_RDONLY), -1, close);
		ASSERT_EQUAL(-1, file.get());
	}

}

void demontrate_unique_resource_with_POSIX_IO_lvalue() {
	const std::string filename = "./hello1.txt";
	auto close=[](auto fd){::close(fd);};
	{
		auto fd = ::open(filename.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0666);

		auto file = make_unique_resource_checked(fd,-1, close);
		ASSERT(fd!=-1);
		::write(file.get(), "Hello World!\n", 12u);
		ASSERT(file.get() != -1);
	}
	{
		std::ifstream input { filename };
		std::string line { };
		getline(input, line);
		ASSERT_EQUAL("Hello World!", line);
		getline(input, line);
		ASSERT(input.eof());
	}
	::unlink(filename.c_str());
	{
		auto fd=::open("nonexistingfile.txt", O_RDONLY);
		auto file = make_unique_resource_checked(fd, -1, close);
		ASSERT_EQUAL(-1, file.get());
	}

}


void test_make_unique_resource_checked(){
	std::ostringstream out{};

	{
		auto bar=make_unique_resource_checked(0.0,0,[&out](auto i){out << i << "not called";});
		auto foo=make_unique_resource_checked(0.0,-1,[&out](auto i){out << "called";});
	}
	ASSERT_EQUAL("called",out.str());

}

struct throwing_copy_movable_resource
{
	throwing_copy_movable_resource(const char* sz, std::ostream &os) :
	sz_ { sz }, out { os } {
	}
	throwing_copy_movable_resource(const throwing_copy_movable_resource &other) :
	out { other.out }
    {
    		using namespace std::literals;
        throw "throwing_copy copy attempt:"s+sz_;
    }
	throwing_copy_movable_resource(throwing_copy_movable_resource && other) noexcept = default;
    bool operator==(int i)const &{
    		return i==0;
    }
    friend std::ostream& operator<<(std::ostream &os,throwing_copy_movable_resource const &t){
    		return os << t.sz_ ;
    }
private:
	const char *sz_ { "" };
    std::ostream &out;
};

bool operator==(std::reference_wrapper<throwing_copy_movable_resource>const&,int i){
		return i==0;
}

void test_make_unique_resource_checked_lvalue(){
	std::ostringstream out{};

	{
		//throwing_copy r{"",out}; // this does not work, make_unique_resource_checked only works for copies
		auto r{0LL};
		auto bar=make_unique_resource_checked(r,0,[&out](auto & i){out << "not called";});
		auto foo=make_unique_resource_checked(r,1,[&out](auto & i){out << "called\n";});
	}
	ASSERT_EQUAL("called\n",out.str());
}
void test_make_unique_resource_checked_failing_copy(){
	std::ostringstream out{};
	{
		throwing_copy_movable_resource x{"x by ref ",out};
		auto bar=make_unique_resource_checked(std::ref(x),0,
				[&out](auto const & i){out << i.get()<<"not called";});
		auto foo=make_unique_resource_checked(std::ref(x),1,
				[&out](auto const & i){out <<i.get() << "called\n";});
	}
	throwing_copy x{"x by value",out};
	try {
		auto bar=make_unique_resource_checked(x,0,[&out](auto const & i){out << i <<"not called";});
	} catch(...){
		out << "expected\n";
	}
	try {
		auto bar=make_unique_resource_checked(x,1,[&out](auto const & i){out << i <<" called\n";});
	} catch(...){
		out << "expected2\n";
	}
	ASSERT_EQUAL("x by ref called\nexpected\nx by value called\nexpected2\n",out.str());

}
void test_make_unique_resource_checked_with_deleter_throwing_on_copy(){
	std::ostringstream out{};
	try {
		auto notcalled=make_unique_resource_checked(0,0,throwing_copy("notcalled",out));
	} catch (...){
		out << "expected\n";
	}
	try{
		auto called   =make_unique_resource_checked(42,0,throwing_copy("called ",out));
	}catch(...){
		out << "expected2\n";
	}
	ASSERT_EQUAL("expected\ncalled 42\nexpected2\n",out.str());
}

void testReferenceWrapper(){
	std::ostringstream out{};
	int i{42};
	{
		auto uref=unique_resource(std::ref(i),[&out](int &j){out << "reference to "<<j++;});
	}
	ASSERT_EQUAL("reference to 42",out.str());
	ASSERT_EQUAL(43,i);
}



void TalkToTheWorld(std::ostream& out, const std::string farewell = "Uff Wiederluege...") {
	// Always say goodbye before returning,
	// but if given a non-empty farewell message use it...
	auto goodbye = scope_exit([&out]()
	{
		out << "Goodbye world..." << std::endl;
	});
	// must pass farewell by reference, otherwise it is not non-throw-moveconstructible
	auto altgoodbye = scope_exit([&out,&farewell]()
	{
		out << farewell << std::endl;
	});

	if (farewell.empty()) {
		altgoodbye.release();		// Don't use farewell!
	} else {
		goodbye.release();	// Don't use the alternate
	}
}

void testTalkToTheWorld() {
	std::ostringstream out { };
	TalkToTheWorld(out, "");
	ASSERT_EQUAL("Goodbye world...\n", out.str());
	out.str("");
	TalkToTheWorld(out);
	ASSERT_EQUAL("Uff Wiederluege...\n", out.str());
}




struct X {
	void foo() const {
	}
};
void testCompilabilityGuardForNonPointerUniqueResource() {
	auto x = unique_resource(X { }, [](X i) {});
	unique_resource y(X { }, [](X i) {});
#if defined(CHECK_COMPILE_ERRORS)
	x->foo();// compile error!
	*x; // compile error!
	y->foo();
	*y;
#endif

}
void testCompilabilityGuardForPointerTypes() {
	auto x = unique_resource(new int { 42 }, [](int * ptr) {delete ptr;});
	ASSERT_EQUAL(42, *x);
	auto y = unique_resource(new X { }, [](X * ptr) {delete ptr;});
	y->foo(); // compiles, SFINAE works
	(void)*y; // compiles, through SFINAE (again)
	ASSERT_EQUAL(42,*(int*)(void*)x.get());
}

struct functor_copy_throws{
	functor_copy_throws()=default;
	functor_copy_throws(const functor_copy_throws &) noexcept(false) {
		throw 42;
	}
	functor_copy_throws(functor_copy_throws &&)=default;
	void operator()(){}
};
struct functor_move_throws{ // bad idea anyway.
	functor_move_throws()=default;
	functor_move_throws(functor_move_throws &&)noexcept(false){ throw 42;}
	functor_move_throws(const functor_move_throws &) = default;
	void operator()()const{}
};

struct functor_move_copy_throws{
	functor_move_copy_throws()=default;
	functor_move_copy_throws(functor_move_copy_throws &&)noexcept(false){ throw 42;}
	functor_move_copy_throws(const functor_move_copy_throws &) noexcept(false) {
		throw 42;
	}
	void operator()()const{}
};


void test_scope_exit_with_throwing_fun_copy(){
	functor_copy_throws fun;
#if defined(CHECK_COMPILE_ERRORS)
	auto x = scope_exit(std::move(fun)); // doesn't compile due to static_assert
	auto x1 = scope_exit(42); // not callable
	auto const &ff=functor_copy_throws{};
	auto z = scope_exit(std::ref(ff)); // hold by const reference
#endif
	auto y = scope_exit(std::ref(fun)); // hold by reference
	ASSERTM("should just work",true);
}

void test_scope_exit_with_throwing_fun_move(){
	functor_move_throws fun;
	const functor_move_throws &funref { fun };
//#if defined(CHECK_COMPILE_ERRORS)
	auto x = scope_exit(std::move(fun)); // no longer a compile error, because it is copied.
//#endif
	auto y = scope_exit(fun); // hold by copy
	auto z = scope_exit(funref); // hold by copy?, no const ref
	ASSERTM("should just work",true);
}
void test_scope_exit_with_throwing_fun_move_and_copy(){
	functor_move_copy_throws fun;
#if defined(CHECK_COMPILE_ERRORS)
	auto x = scope_exit(std::move(fun)); // compile error, because non-copyable
#endif
	auto y = scope_exit(std::ref(fun)); // hold by reference works
	ASSERTM("should not work",true);
}

void test_scope_success_with_side_effect(){
	std::ostringstream out{};
	auto lam=[&]{out << "not called";};
	try{
		auto x=scope_success(lam); // lam not called
		throw 42;
	}catch(...){
		auto y=scope_success([&]{out << "handled";});
	}
	ASSERT_EQUAL("handled",out.str());
}
void test_scope_success_might_throw(){
	std::ostringstream out{};
	auto lam=[&]{out << "called"; /* throw 42;*/}; // doesn't work.
	try{{
		auto x=scope_success(lam);
		}
		//out << " never ";
	} catch (int) {
		// OK
	} catch (...) {
		out << "bla";
	}
	ASSERT_EQUAL("called",out.str());
}



void demo_scope_exit_fail_success(){
	std::ostringstream out{};
	auto lam=[&]{out << "called ";};
	try{
		auto v=scope_exit([&]{out << "always ";});
		auto w=scope_success([&]{out << "not ";}); // not called
		auto x=scope_fail(lam); // called
		throw 42;
	}catch(...){
		auto y=scope_fail([&]{out << "not ";}); // not called
		auto z=scope_success([&]{out << "handled";}); // called
	}
	ASSERT_EQUAL("called always handled",out.str());
}

void demo_scope_exit_fail_success_Cpp17(){
	std::ostringstream out{};
	auto lam=[&]{out << "called ";};
	try{
		scope_exit v([&]{out << "always ";});
		scope_success w([&]{out << "not ";}); // not called
		scope_fail x(lam); // called
		throw 42;
	}catch(...){
		scope_fail y([&]{out << "not ";}); // not called
		scope_success z([&]{out << "handled";}); // called
	}
	ASSERT_EQUAL("called always handled",out.str());
}


void test_scope_exit_lvalue_ref_passing_rvalue_fails_to_compile(){
	typedef void (*fun)();
	auto y = scope_exit<const fun &>(fun(nullptr)); // no static assert needed. fails to match.
	y.release(); // avoid crash from calling nullptr
	scope_exit<const fun&> z(fun(nullptr));
	z.release();// avoid crash from calling nullptr
	scope_exit zz(fun(nullptr));
	zz.release();
#if defined(CHECK_COMPILE_ERRORS)
	auto x=scope_exit<fun  &>(fun(nullptr)); // no static assert needed. fails to match
	std::experimental::scope_exit<const fun&> se { fun(nullptr) }; // static assert needed
	scope_exit se17 { fun(nullptr) }; // static assert needed
#endif


}


struct nasty{};

struct deleter_2nd_throwing_copy {
	deleter_2nd_throwing_copy()=default;
	deleter_2nd_throwing_copy(deleter_2nd_throwing_copy const &other){
		if (copied %2) {
			throw nasty{};
		}
		++copied;
	}
	void operator()(int const & t) const {
		++deleted;
	}
	static inline int deleted{};
	static inline int copied{};
};

void test_sometimes_throwing_deleter_copy_ctor(){
	using uid=unique_resource<int,deleter_2nd_throwing_copy>;
	uid strange{1,deleter_2nd_throwing_copy{}};
	ASSERT_EQUAL(0,deleter_2nd_throwing_copy::deleted);

	strange.release();
	ASSERT_EQUAL(0,deleter_2nd_throwing_copy::deleted);

	try {
		uid x{ std::move(strange)};
		FAILM("should have thrown");
	} catch(nasty const &){
	}
	ASSERT_EQUAL(0,deleter_2nd_throwing_copy::deleted);
	ASSERT_EQUAL(1,deleter_2nd_throwing_copy::copied);
}


void runAllTests(int argc, const char *argv[]) {
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testPtrPairThrowingCtor));
	s.push_back(CUTE(testscopeExitWithNonAssignableResourceAndReset));
	s.push_back(CUTE(testCompilabilityGuardForPointerTypes));
	s.push_back(CUTE(testTalkToTheWorld));
	s.push_back(CUTE(demontrate_unique_resource_with_POSIX_IO));
	s.push_back(CUTE(demontrate_unique_resource_with_POSIX_IO_lvalue));
	s.push_back(CUTE(demonstrate_unique_resource_with_stdio));
	s.push_back(CUTE(demonstrate_unique_resource_with_stdio_Cpp17));
	s.push_back(CUTE(test_unique_resource_semantics_reset));
	s.push_back(CUTE(testUniqueResourceSimple));
	s.push_back(CUTE(testThrowOnUniqueResourceDoesntCrashIt));
	s.push_back(CUTE(testThrowDoesntCrashIt));
	s.push_back(CUTE(testDismissedGuard));
	s.push_back(CUTE(testUniqueResourceByReference));
	s.push_back(CUTE(test_scope_exit_with_throwing_fun_copy));
	s.push_back(CUTE(test_scope_success_with_side_effect));
	s.push_back(CUTE(demo_scope_exit_fail_success));
	s.push_back(CUTE(demo_scope_exit_fail_success_Cpp17));
	s.push_back(CUTE(test_scope_exit_lvalue_ref_passing_rvalue_fails_to_compile));
	s.push_back(CUTE(test_scope_success_might_throw));
	s.push_back(CUTE(test_make_unique_resource_checked));
	s.push_back(CUTE(test_make_unique_resource_checked_lvalue));
	s.push_back(CUTE(test_make_unique_resource_checked_failing_copy));
	s.push_back(CUTE(test_make_unique_resource_checked_with_deleter_throwing_on_copy));
	s.push_back(CUTE(testReferenceWrapper));
	s.push_back(CUTE(testScopeExitWithReferenceWrapper));
	s.push_back(CUTE(testsFromEricNiebler_scope_exit_with_throwing_function_object));
	s.push_back(CUTE(testsFromEricNiebler_scope_success_with_throwing_function_object));
	s.push_back(CUTE(testsFromEricNiebler_scope_fail_with_throwing_function_object));
	s.push_back(CUTE(testScopeExitWithCPP17DeducingCtors));
	s.push_back(CUTE(testScopeFailWithCPP17DeducingCtors));
	s.push_back(CUTE(testScopeSuccessWithCPP17DeducingCtors));
	s.push_back(CUTE(test_sometimes_throwing_deleter_copy_ctor));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, const char *argv[]) {
    runAllTests(argc,argv);
    return 0;
}



