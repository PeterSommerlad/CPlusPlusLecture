#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"


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
