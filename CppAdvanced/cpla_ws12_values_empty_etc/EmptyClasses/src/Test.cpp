#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <type_traits>


void testEmptyTraits() {
	ASSERT_EQUAL(1u,sizeof(std::true_type)); // not really empty, but
}

struct empty{};
static_assert(sizeof(empty)>0
  && sizeof(empty)<sizeof(int),
  "there should be something");

struct plain{
	int x;
};
static_assert(sizeof(plain)==sizeof(int),
  "no additional overhead");

struct combined:plain,empty{
};
static_assert(sizeof(combined)==sizeof(plain),
  "empty base class should not add size");

struct ebo :  empty{
	empty e;
	int i;
};
static_assert(sizeof(ebo)==2*sizeof(int),
  "ebo must not work");
struct noebo: empty{
	ebo e;
	int i;
};
static_assert(sizeof(noebo)==4*sizeof(int),
  "same type subojects must have unique addresses");

void demonstrateEBOsimple(){
	ASSERT_EQUAL(sizeof(int),sizeof(plain));
	ASSERT_EQUAL(sizeof(plain),sizeof(combined));
}

template<class T, T v>
struct integral_constant {
    using value_type=T;
    static constexpr value_type value = v;
    using type=integral_constant; // using injected-class-name
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};
using true_type=integral_constant<bool,true>;

static_assert(integral_constant<bool,true>::value,"");
static_assert(true_type::value,"member access");
static_assert(true_type{},"auto-conversion");
static_assert(true_type{}(),"call operator");
static_assert(std::is_same_v<true_type, true_type::type>,"type meta");

std::integer_sequence<int,1,2,3,4> a{};

void demonstrate_type_queries(){
	using namespace std;
	ASSERT(is_integral_v<int>);
	ASSERT(not is_integral_v<double>);
	ASSERT(is_reference_v<int&>);
	ASSERT(not is_object_v<decltype(demonstrate_type_queries)>);
	ASSERT(is_object_v<int>);
	ASSERT(not is_object_v<int&>);
}

template <typename T>
struct Sack{
	static_assert(std::is_object_v<T> && !std::is_pointer_v<T>,
			"you can not use Sack with references or pointers");
};

Sack<int> sack;
//Sack<int*> ptrsack;
//Sack<int&> refsack;

void demonstrate_type_composition(){
	using T=int;
	using namespace std;


	using I=decltype(42L);
	using U=make_unsigned_t<I>;
	using S=typename make_signed<U>::type;

	using X=int const volatile[5];
	using X1=remove_all_extents_t<X>;
	ASSERT((is_same_v<X1,int const volatile>));
	using X2=remove_cv_t<X1>;
	ASSERT((is_same_v<X2,int>));
	using RCV=int const volatile &; // cv ref to plain
	ASSERT((is_same_v<int,decay_t<RCV>>));
	using FR=void(&)(int); // func to funcptr
	ASSERT((is_same_v<void(*)(int),decay_t<FR>>));
	using AR=int const [42]; // array to ptr
	ASSERT((is_same_v<int const *,decay_t<AR>>));

	using Tref=add_lvalue_reference_t<T>;
	using Tcref=add_const_t<Tref>;
	using Tptr=add_pointer_t<T>;

}

namespace Pu{
template <typename V, typename TAG>
struct Unit {
	static_assert(std::is_object_v<V>,"must keep real values");
	V val;
	static inline constexpr bool __is_unit{true}; // hack for V compatibility
};


template <typename U>
struct Inc{
	friend constexpr auto operator++(U &rv){
		return ++rv.val;
	}
	friend constexpr auto operator++(U &rv,int){
		auto res=rv;
		++rv;
		return res;
	}
};

template <typename T, typename = void>
struct is_unit;
template <typename U>
struct is_unit<U, std::enable_if_t<U::__is_unit>>:std::true_type{};
template <typename V>
struct is_unit<V>:std::false_type{};


template <typename T>
constexpr bool is_unit_v=is_unit<T>::value;

template <typename U, typename V=U>
struct Eq{
	//static_assert(is_unit_v<U>, "can only be attached to Units");
	friend constexpr
	bool
	operator==(U const &l, U const& r){
		return l.val == r.val;
	}
	friend constexpr std::enable_if_t<!std::is_same_v<U,V>,bool>
	operator==(U const &l, V const& r){
		if constexpr (is_unit_v<V>)
			return l.val == r.val;
		else
			return l.val == r;
	}
	friend constexpr std::enable_if_t<!std::is_same_v<U,V>,bool>
	operator==(V const &l, U const& r){
		return r == l;
	}
	friend constexpr bool
	operator!=(U const &l, V const& r){
		return !(l==r);
	}
	friend constexpr std::enable_if_t<!std::is_same_v<U,V>,bool>
	operator!=(V const &l, U const& r){
		return !(l==r);
	}
};


struct WaitC:Unit<unsigned,WaitC>
,Inc<WaitC>
,Eq<WaitC,unsigned>{
};
static_assert(std::is_standard_layout_v<WaitC>,"standard layout");
static_assert(sizeof(WaitC)==sizeof(unsigned),"works?");
}

void testAWaitCounterUnit(){
	using namespace Pu;
	WaitC wc{42};
	++wc;
	ASSERT_EQUAL(43u,wc);
	ASSERT(wc!=42u);
	ASSERT_EQUAL(WaitC{43},wc);
}



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testEmptyTraits));
	s.push_back(CUTE(demonstrateEBOsimple));
	s.push_back(CUTE(demonstrate_type_queries));
	s.push_back(CUTE(demonstrate_type_composition));
	s.push_back(CUTE(testAWaitCounterUnit));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
