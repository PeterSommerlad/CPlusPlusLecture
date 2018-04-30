#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <memory>
struct nasty{};

struct ctor_2nd_throws {
	ctor_2nd_throws(){
		if (created %2) {
			throw nasty{};
		}
		++created;
	}
	~ctor_2nd_throws() {
		++deleted;
	}
	static void reset(){
		deleted=0;created=0;
	}
	static inline int deleted{};
	static inline int created{};
};

template <typename T>
struct PtrPair{
	PtrPair()
	:one{new T{}},two{new T{}}{}
	~PtrPair()
	noexcept(noexcept(delete std::declval<T*>()))
	{
		delete one;
		delete two;
	}
private:
	T* one{};
	T* two{};
};
template <typename T>
struct SafePtrPair{
//	SafePtrPair() try
//	:one{new T{}},two{new T{}}
//	{
//	} catch(...) {
//		delete one;
//		delete two; // throws, uninitialized ptr
//		// automatically re-throws: throw;
//	}

	SafePtrPair() try
	{
		one = new T{};
		two = new T{};
	} catch(...) {
		delete one;
		delete two;
		// automatically re-throws: throw;
	}
	~SafePtrPair()
	noexcept(false)
	try {
		delete one;
		delete two;
	} catch(...){

	//	return; // include and remvoe noexcept(false)
	}
private:
	T* one{};
	T* two{};
};

template <typename T>
struct SaferPtrPair{
	SaferPtrPair()
	:one{std::make_unique<T>()},two{std::make_unique<T>()}{}
private:
	std::unique_ptr<T> one{};
	std::unique_ptr<T> two{};
};


struct dtor_2nd_throws {
	dtor_2nd_throws(){
		++created;
	}
	~dtor_2nd_throws() noexcept(false) {
		if (deleted %2 ) {
			throw nasty{};
		}
		++deleted;
	}
	static void reset(){
		deleted=0;created=0;
	}
	static inline int deleted{};
	static inline int created{};
};


void testPtrPairThrowingCtor() {
	ctor_2nd_throws::reset();

	ASSERT_THROWS(PtrPair<ctor_2nd_throws>{},nasty);
	ASSERT_EQUAL(1,ctor_2nd_throws::created);
	ASSERT_EQUAL(1,ctor_2nd_throws::deleted);
}
void testSafePtrPair() {
	ctor_2nd_throws::reset();
	ASSERT_THROWS(SafePtrPair<ctor_2nd_throws>{},nasty);
	ASSERT_EQUAL(1,ctor_2nd_throws::deleted);
	ASSERT_EQUAL(1,ctor_2nd_throws::created);
}
void testSaferPtrPair() {
	ctor_2nd_throws::reset();
	ASSERT_THROWS(SaferPtrPair<ctor_2nd_throws>{},nasty);
	ASSERT_EQUAL(1,ctor_2nd_throws::deleted);
	ASSERT_EQUAL(1,ctor_2nd_throws::created);
}

void testSaferPtrPairThrowingDestructor(){
	dtor_2nd_throws::reset();
	try {{
		SaferPtrPair<dtor_2nd_throws> p{};
	}
	FAILM("expected throwing");
	} catch(nasty const &){

	} catch(...){
		FAILM("something bad happened");
	}
}
void testSafePtrPairThrowingDestructor(){
	dtor_2nd_throws::reset();
	try {{
		SafePtrPair<dtor_2nd_throws> p{};
	}
	FAILM("expected throwing");
	} catch(nasty const &){
	} catch(cute::test_failure const &){
		throw;
	}
	catch(...){
		FAILM("something bad happened");
	}
	ASSERT_EQUAL(2,dtor_2nd_throws::created);
	ASSERT_EQUAL(1,dtor_2nd_throws::deleted);
}

void testPtrPairThrowingDestructor(){
	dtor_2nd_throws::reset();
	try {{
		PtrPair<dtor_2nd_throws> p{};
	}
	FAILM("expected throwing");
	} catch(nasty const &){ // expected
	} catch(cute::test_failure const &){
		throw;
	}
	catch(...){
		FAILM("something bad happened");
	}
	ASSERT_EQUAL(2,dtor_2nd_throws::created);
	ASSERT_EQUAL(1,dtor_2nd_throws::deleted);
}





bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testPtrPairThrowingCtor));
	s.push_back(CUTE(testSafePtrPair));
	s.push_back(CUTE(testSaferPtrPair));
	s.push_back(CUTE(testSafePtrPairThrowingDestructor));
	s.push_back(CUTE(testPtrPairThrowingDestructor));
	s.push_back(CUTE(testSaferPtrPairThrowingDestructor));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
