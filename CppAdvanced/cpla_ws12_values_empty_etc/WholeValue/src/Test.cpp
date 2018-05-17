#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <cassert>

#include <array>

#include <string>

#include <utility>

#include <vector>

#include <sstream>

template <typename TAG>
struct Counter{
	size_t count{};
	bool operator==(Counter const &other) const {
		return count == other.count;
	}
	Counter& operator++(){
		++count;
		return *this;
	}
};
struct Wait:Counter<Wait> {
};
static_assert(sizeof(Wait)==sizeof(size_t),"no overhead added");
struct Notify:Counter<Notify> {
};
struct BadWaits:Counter<BadWaits>{
};

struct Waits {
	size_t count{};
};
void operator++(Waits& w){
	w.count++;
}
struct Notifies {
	size_t count{};
};
void operator++(Notifies& n){
	n.count++;
}


struct CounterBase{
	size_t count;
	void operator++(){ // what to return?
		++count;
	}
	bool operator==(CounterBase const &other)const{
		return count==other.count;
	}
};

struct WaitB:CounterBase{};
struct NotifiesB:CounterBase{};



void CompareWaitsWithNotifies() {
	WaitB waits{5};
	ASSERT_EQUAL(NotifiesB{5},waits);
}
void CompareWaitsWithNotifiesCRTP() {
	Wait waits{5};
//	ASSERT_EQUAL(Notify{5},waits); // does not compile
}

void DemonstrateRegular(){
	using T=int;
	using std::swap;

	T a{}; // default constructible
	T b=a; // copy-initialize
	assert(b==a); // equality comparable (transitive)
	T c{};
	c = b; // assignable
	swap(c,b); // swappable
	assert(c==b && c== a); // transitive comparable
	++a; // change it to something else
	assert(a != b);
	a.~T(); // destructible

	{
		T val{}; // default constructed, value or aggregate initialized
		T u; // default constructed, but may be uninitialized
		T(); // temporary default value - value initialized
		T{}; // temporary default value - aggreate initialized
		T arr[10] { }; // array, better std::array
		std::array<T,10> sa{};
		std::vector<T> v(2); // uses default value for init
	}
}
void DemonstrateMovable(){
	using T=int;
	using std::swap;

	T a{};
	T b=std::move(a); // move-initialize
	//assert(b==a);
	T c{std::move(b)};
	b = std::move(c); // reassign
	a.~T(); // destroy
	c = T{}; // move assignment - rvalue
	swap(b,c); // swap efficient
}
void DemonstrateSwappable(){
	using T=long long;
	using U=int64_t;

	T a{};
	T b{};
	using std::swap;
	swap(a,b);
	static_assert(std::is_swappable_v<T>,"");
	U c{};
	swap(b,c);
	static_assert(std::is_same_v<T,U>,"");
	static_assert(std::is_swappable_with_v<T&,U&>,"");
}

template <typename EF>
struct naive_scope_exit {
	template <typename EFP>
	naive_scope_exit(EFP &&ef)
	:f(std::forward<EFP>(ef))
	{
	}
	~naive_scope_exit(){
		f();
	}
private:
	EF f;
	naive_scope_exit(naive_scope_exit const&)=delete;
};
template <typename EF>
naive_scope_exit(EF)->naive_scope_exit<EF>;

std::string foo(std::ostream &out){
	std::string res="verylongstringtosidestepsmallstringoptimizationandevenlongerforyou";
	naive_scope_exit ex([&out,&res]{ out << res.size() << ":" << res  ;});
	return res;//std::move(res);
}

void DemonstrateNaiveScopeExitProblem(){
	std::ostringstream out{};
	std::string res=foo(out);
	ASSERT_EQUAL("66:"+res,out.str());

}




bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(CompareWaitsWithNotifies));
	s.push_back(CUTE(CompareWaitsWithNotifiesCRTP));
	s.push_back(CUTE(DemonstrateRegular));
	s.push_back(CUTE(DemonstrateNaiveScopeExitProblem));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
