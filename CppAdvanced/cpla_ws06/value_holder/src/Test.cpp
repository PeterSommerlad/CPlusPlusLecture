#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <stdexcept>
#include <utility>
#include <cstddef>

template<typename T>
struct bad_get: std::logic_error {
	bad_get() :
			logic_error{typeid(T).name()} {
	}
};

namespace detail {

auto const no_op_del = [](std::byte *) noexcept {};

}

struct value_holder {
	value_holder() = default;

	template<typename T, typename = std::enable_if_t<!std::is_array<std::remove_reference_t<T>>::value>>
	value_holder(T && value) :
			pv{allocate(std::forward<T>(value))}, del{make_deleter<std::decay_t<T>>()} {
	}

	value_holder(value_holder const &) = delete;

	value_holder(value_holder &) = delete;

	value_holder(value_holder && rhs) noexcept :
			value_holder{} {
		std::swap(pv, rhs.pv);
		std::swap(del, rhs.del);
	}

	~value_holder() {
		del(pv);
		delete[] pv;
	}

	explicit operator bool() const {
		return pv != nullptr;
	}

	void clear() {
		del(pv);
		delete pv;
		pv = nullptr;
	}

	template<typename T>
	T const & get() const {
		if (pv) {
			return *reinterpret_cast<T const *>(pv);
		}
		throw bad_get<T>{};
	}

	template<typename T>
	value_holder& operator=(T && val) {
		del(pv);
		del = detail::no_op_del; // ensure an exception won't break this
		delete[] pv;
		pv = nullptr;
		pv = allocate(std::forward<T>(val));
		del = make_deleter<std::decay_t<T>>();
		return *this;
	}

	value_holder& operator=(value_holder const &rhs) = delete;

	value_holder& operator=(value_holder &rhs) = delete;

	value_holder& operator=(value_holder &&rhs) {
		del(pv);
		del = detail::no_op_del;
		delete[] pv;
		pv = nullptr;
		std::swap(pv, rhs.pv);
		std::swap(del, rhs.del);
		return *this;
	}

private:
	std::byte * pv{};

	using DELTYPE = void(*)(std::byte *);

	DELTYPE del{detail::no_op_del}; // no op

	template<typename T>
	static std::byte *allocate(T && value) {
		auto p = new std::byte[sizeof(std::decay_t<T>)];
		new (p) std::remove_reference_t<T>{std::forward<T>(value)};
		return p;
	}

	template<typename T>
	static DELTYPE make_deleter() {
		return [](std::byte *p)noexcept {
			if (p) {
				reinterpret_cast<std::decay_t<T>*>(p)->~T();
			}
		};
	}
};

struct simple_holder {

	simple_holder() = default;

	template<typename T>
	simple_holder(T const &value) :
			pv{new std::byte[sizeof(T)]}, del{make_deleter<T>()} {
		new (pv) T{value}; // placement new
	}

	~simple_holder() {
		del(pv); // destroy a T
		delete[] pv;
	}

	explicit operator bool() const {
		return pv != nullptr;
	}

	simple_holder(simple_holder const &) = delete;

	simple_holder(simple_holder &&rhs) noexcept :
			simple_holder{} {
		std::swap(pv, rhs.pv);
		std::swap(del, rhs.del);
	}

	void clear() {
		del(pv);
		delete pv;
		pv = nullptr;
	}

	template<typename T>
	T const & get() const {
		if (pv)
			return *reinterpret_cast<T const *>(pv);
		throw bad_get<T> {};
	}

	template<typename T>
	simple_holder& operator=(T const & val) {
		del(pv);
		delete[] pv;
		pv = new std::byte[sizeof(T)];
		new (pv) T{val};
		del = make_deleter<T>();
		return *this;
	}

	simple_holder& operator=(simple_holder const &rhs) = delete; // would need to memorize size as well

	simple_holder& operator=(simple_holder &&rhs) {
		del(pv);
		del = [](std::byte *) {};
		delete[] pv;
		pv = nullptr;
		std::swap(pv, rhs.pv);
		std::swap(del, rhs.del);
		return *this;
	}

private:
	std::byte *pv{};

	using DELTYPE=void(*)(std::byte *);

	DELTYPE del{[](std::byte *) {}}; // no op

	template<typename T>
	static DELTYPE make_deleter() {
		return [](std::byte *p) {if(p)reinterpret_cast<T*>(p)->~T();};
	}
};

void thisIsATest() {
	value_holder i{}; // empty
	ASSERTM("value is undefined", !i);
}
void testWithValue() {
	value_holder v{42};
	ASSERTM("value is defined", bool(v));
	ASSERT_EQUAL(42, v.get<int>());
	v.clear();
	ASSERT_THROWS(v.get<int>(), bad_get<int>);
}

void testWithReassign() {
	using namespace std::string_literals;
	value_holder i{};
	ASSERTM("undefined value", !i);
	i = 42;
	ASSERTM("defined value", bool(i));
	ASSERT_EQUAL(42, i.get<int>());
	i = "hallo"s;
	ASSERT_EQUAL("hallo"s, i.get<std::string>());
	i.clear();
	ASSERT_THROWS(i.get<int>(), bad_get<int>);
}
void testSimpleEmpty() {
	simple_holder i{}; // empty
	ASSERTM("value is undefined", !i);
}
void testSimpleWithValue() {
	simple_holder v{42};
	ASSERTM("value is defined", bool(v));
	ASSERT_EQUAL(42, v.get<int>());
	v.clear();
	ASSERT_THROWS(v.get<int>(), bad_get<int>);
}

void testSimpleWithReassign() {
	using namespace std::string_literals;
	simple_holder i{};
	ASSERTM("undefined value", !i);
	i = 42;
	ASSERTM("defined value", bool(i));
	ASSERT_EQUAL(42, i.get<int>());
	i = "hallo"s;
	ASSERT_EQUAL("hallo"s, i.get<std::string>());
	i.clear();
	ASSERT_THROWS(i.get<int>(), bad_get<int>);
}
struct tracer {
	tracer(std::ostream &os) :
			out{os} {
		out.get() << "tracer ctor" << std::endl;
	}
	~tracer() {
		out.get() << "~tracer" << std::endl;
	}
	tracer(tracer &&rhs) :
			out{rhs.out} {
		out.get() << "tracer move ctor" << std::endl;
	}
	tracer &operator=(tracer &&rhs) {
		out = rhs.out;
		out.get() << "tracer move assign" << std::endl;
		return *this;
	}
	tracer(tracer const &rhs) :
			out{rhs.out} {
		out.get() << "tracer copy ctor" << std::endl;
	}
	tracer &operator=(tracer const&rhs) {
		out = rhs.out;
		out.get() << "tracer copy assign" << std::endl;
		return *this;
	}
	std::reference_wrapper<std::ostream> out;
};
void testDtor() {
	std::ostringstream os{};
	{
		value_holder sh{tracer{os}};
	}
	ASSERT_EQUAL("tracer ctor\ntracer move ctor\n~tracer\n~tracer\n", os.str());
}
void testSimpleDtor() {
	std::ostringstream os{};
	{
		simple_holder sh{tracer{os}};
	}
	ASSERT_EQUAL("tracer ctor\ntracer copy ctor\n~tracer\n~tracer\n", os.str());
}

void testSimpleMoveCtor() {
	std::ostringstream os{};
	simple_holder sh{tracer{os}};
	ASSERT_EQUAL("tracer ctor\ntracer copy ctor\n~tracer\n", os.str());
	ASSERTM("defined value", bool(sh));
	sh = simple_holder{};
	ASSERTM("no defined value", !sh);
	ASSERT_EQUAL("tracer ctor\ntracer copy ctor\n~tracer\n~tracer\n", os.str());
}

void testMoveCtor() {
	std::ostringstream os{};
	value_holder sh{tracer{os}};
	ASSERTM("defined value", bool(sh));
	sh = value_holder{};
	ASSERTM("no defined value", !sh);
	ASSERT_EQUAL("tracer ctor\ntracer move ctor\n~tracer\n~tracer\n", os.str());
}

void testLvalueArgumentForCtor() {
	std::ostringstream os{};
	tracer tr{os};
	value_holder sh{tr};
	ASSERTM("defined value", bool(sh));
	sh = value_holder{};
	ASSERTM("no defined value", !sh);
	ASSERT_EQUAL("tracer ctor\ntracer copy ctor\n~tracer\n", os.str());
}

void testLvalueArgumentForAssignment() {
	std::ostringstream os{};
	tracer tr{os};
	value_holder sh{};
	sh = tr;
	ASSERTM("defined value", bool(sh));
	sh = value_holder{};
	ASSERTM("no defined value", !sh);
	ASSERT_EQUAL("tracer ctor\ntracer copy ctor\n~tracer\n", os.str());
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	s.push_back(CUTE(testWithValue));
	s.push_back(CUTE(testWithReassign));
	s.push_back(CUTE(testSimpleEmpty));
	s.push_back(CUTE(testSimpleWithValue));
	s.push_back(CUTE(testSimpleWithReassign));
	s.push_back(CUTE(testSimpleMoveCtor));
	s.push_back(CUTE(testMoveCtor));
	s.push_back(CUTE(testDtor));
	s.push_back(CUTE(testSimpleDtor));
	s.push_back(CUTE(testLvalueArgumentForAssignment));
	s.push_back(CUTE(testLvalueArgumentForCtor));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

