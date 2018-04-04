#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <typeindex>
#include <utility>
#include <stdexcept>
#include <cstddef>
#include <sstream>

template<typename T>
struct bad_get : std::logic_error {
	bad_get() :
			logic_error{typeid(T).name()} {
	}
};
namespace detail {

auto const no_op_del = [](std::byte *)noexcept {};

auto const no_op_copy = [](std::byte const *)-> std::byte * {return nullptr;};

}

struct value_holder {
	value_holder() = default;

	template<typename T, typename = std::enable_if_t<
			(!std::is_same<std::decay_t<T>, value_holder>::value && !std::is_array<std::remove_reference_t<T>>::value)> >
	value_holder(T &&value) :
			pv{allocate(std::forward<T>(value))},
			del{make_deleter<std::decay_t<T>>()},
			cop{make_copier<std::decay_t<T>>()},
			id{typeid(std::decay_t<T>)} {
	}

	value_holder(value_holder const &rhs) :
			pv{rhs.cop(rhs.pv)},
			del{rhs.del},
			cop{rhs.cop},
			id{rhs.id} {
	}

	value_holder(value_holder &&rhs) noexcept :
			value_holder{} {
		std::swap(pv, rhs.pv);
		std::swap(del, rhs.del);
		std::swap(cop, rhs.cop);
		std::swap(id, rhs.id);
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
			std::type_index const other{typeid(T)};
			if (other == id)
				return *reinterpret_cast<T const *>(pv);
		}
		throw bad_get<T>{};
	}

	template<typename T, typename = std::enable_if_t<
			(!std::is_same<std::decay_t<T>, value_holder>::value && !std::is_array<std::remove_reference_t<T>>::value)>>
	value_holder& operator=(T && val) {
		del(pv);
		del = detail::no_op_del; // ensure an exception won't break this
		delete[] pv;
		pv = nullptr;
		pv = allocate(std::forward<T>(val));
		del = make_deleter<std::decay_t<T>>();
		id = typeid(std::decay_t<T>);
		return *this;
	}

	value_holder& operator=(value_holder &&rhs) {
		del(pv);
		del = detail::no_op_del;
		cop = detail::no_op_copy;
		delete[] pv;
		pv = nullptr;
		id = typeid(void);
		std::swap(pv, rhs.pv);
		std::swap(del, rhs.del);
		std::swap(id, rhs.id);
		return *this;
	}

	value_holder& operator=(value_holder const &rhs) {
		del(pv);
		delete[] pv;
		pv = rhs.cop(rhs.pv);
		del = rhs.del;
		cop = rhs.cop;
		id = rhs.id;
		return *this;
	}

	// to allow copying, one needs to memorize not only the deleter, but also the copy-operation
	// std::any uses a manager object and small object optimization to do so.
private:
	std::byte * pv{};
	using DELTYPE = void(*)(std::byte *);
	DELTYPE del{detail::no_op_del}; // no op
	using COPYTYPE = std::byte *(*)(std::byte const *);
	COPYTYPE cop{detail::no_op_copy};
	std::type_index id{typeid(void)};

	template<typename T>
	static std::byte *allocate(T && value) {
		auto p = new std::byte[sizeof(std::decay_t<T>)];
		new (p) std::decay_t<T>{std::forward<T>(value)};
		return p;
	}

	template<typename T>
	static DELTYPE make_deleter() {
		return [](std::byte *p)noexcept {if(p)reinterpret_cast<std::decay_t<T>*>(p)->~T();};
	}

	template<typename T>
	static COPYTYPE make_copier() {
		return [](std::byte const *s) -> std::byte *
		{
			if (s) {
				std::byte * const p = new std::byte[sizeof(std::decay_t<T>)];
				new (p) std::decay_t<T> {*reinterpret_cast<std::decay_t<T> const *>(s)};
				return p;
			}
			return nullptr;
		};
	}
};

void thisIsATest() {
	value_holder i{}; // empty
	ASSERTM("value is undefined", !static_cast<bool>(i));
}
void testWithValue() {
	value_holder v{42};
	ASSERTM("value is defined", bool(v));
	ASSERT_EQUAL(42, v.get<int>());
	v.clear();
	ASSERT_THROWS(v.get<int>(), bad_get<int>);
}
void testWithWrongGet() {
	value_holder v{42};
	ASSERT_EQUAL(42, v.get<int>());
	ASSERT_THROWS(v.get<short>(), bad_get<short>);

}

void testWithReassign() {
	using namespace std::string_literals;
	value_holder i{};
	ASSERTM("undefined value", !bool(i));
	i = 42;
	ASSERTM("defined value", bool(i));
	ASSERT_EQUAL(42, i.get<int>());
	i = "hallo"s;
	ASSERT_EQUAL("hallo"s, i.get<std::string>());
	i.clear();
	ASSERT_THROWS(i.get<int>(), bad_get<int>);
}
void testWithCopyCtor() {
	value_holder i{42};
	value_holder j{i};
	ASSERT_EQUAL(42, j.get<int>());
}
void testWithCopyAssign() {
	value_holder i{42};
	value_holder j{};
	j = i;
	ASSERT_EQUAL(42, j.get<int>());
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
	s.push_back(CUTE(testMoveCtor));
	s.push_back(CUTE(testDtor));
	s.push_back(CUTE(testLvalueArgumentForAssignment));
	s.push_back(CUTE(testLvalueArgumentForCtor));
	s.push_back(CUTE(testWithWrongGet));
	s.push_back(CUTE(testWithCopyCtor));
	s.push_back(CUTE(testWithCopyAssign));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

