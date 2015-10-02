/*******************************************************************************
 * Copyright (c) 2012, IFS Institute for Software, HSR Rapperswil,
 * Switzerland, http://ifs.hsr.ch
 *
 * Permission to use, copy, and/or distribute this software for any
 * purpose without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 ******************************************************************************/

#ifndef MOCKATOR_H_
#define MOCKATOR_H_

#if defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus >= 201103L)
# define USE_STD11 1
#endif

#if !defined(USE_STD11)
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
# include <boost/preprocessor/repetition/enum_trailing_params.hpp>
# include <boost/assign/std/vector.hpp>
#endif

#include <cxxabi.h>
#include <sstream>
#include <set>
#include <boost/regex.hpp>

namespace mockator {
// the following code was taken and slightly adapted from Boost's exception library
// it avoids compile errors if a type used with ASSERT_EQUALS doesn't provide an output shift operator
namespace to_string_detail {

template<typename T, typename CharT, typename Traits>
char operator<<(std::basic_ostream<CharT, Traits> &, T const&);

template<typename T, typename CharT, typename Traits>
struct is_output_streamable_impl {
	static std::basic_ostream<CharT, Traits>& f();

	static T const& g();

	enum e {
		value = (sizeof(char) != sizeof(f() << g()))
	};
};

template<class CONT>
struct has_begin_end_const_member {
	template<typename T, T, T> struct type_check;

	template<typename C> static typename C::const_iterator test(
			type_check<typename C::const_iterator (C::*)() const, &C::begin,
					&C::end>*);

	template<typename C> static char test(...);

	enum e {
		value = (sizeof(char) != sizeof(test<CONT>(0)))
	};
};
}

template<typename T, bool select>
struct select_built_in_shift_if {
	std::ostream& os;

	select_built_in_shift_if(std::ostream& ros) : os(ros) {
	}

	std::ostream& operator()(T const& t) {
		return os << t; // default uses operator<<(std::ostream&,T const&)
	}
};

template<typename T, typename CharT = char, typename Traits = std::char_traits<CharT> >
struct is_output_streamable {
	enum e {
		value = to_string_detail::is_output_streamable_impl<T, CharT, Traits>::value
	};
};

template<typename T>
std::ostream &toStream(std::ostream &os, T const& t) {
	select_built_in_shift_if<T, is_output_streamable<T>::value> out(os);
	return out(t);
}

// detect standard container conforming begin() end() iterator accessors.
// might employ begin/end traits from c++11 for loop in the future. --> select_container
template<typename T>
struct WithDelimiterPrinter {
	std::ostream &os;
	bool first; // allow use of for_each algorithm

	WithDelimiterPrinter(std::ostream &os) : os(os), first(true) {
	}

	void operator()(T const &t) {
		if (!first)
			os << ',';
		else
			first = false;
		os << '\n'; // use newlines so that CUTE's plug-in result viewer gives nice diffs
		toStream<T>(os, t);
	}
};

// taken from CUTE
inline std::string demangle(char const* name) {
	if (!name)
		return "unknown";
	char *toBeFreed = abi::__cxa_demangle(name, 0, 0, 0);
	std::string result(toBeFreed ? toBeFreed : name);
	::free(toBeFreed);
	return result;
}

// try print_pair with specialization of template function instead:
// the generic version prints about missing operator<< that is the last resort
template<typename T>
std::ostream &print_pair(std::ostream &os, T const&) {
	return os << "operator<< not defined for type "
			<< demangle(typeid(T).name());
}

// the std::pair overload is useful for std::map etc. however,
template<typename K, typename V>
std::ostream &print_pair(std::ostream &os, std::pair<K, V> const& p) {
	os << '[';
	toStream(os, p.first);
	os << " -> ";
	toStream(os, p.second);
	os << ']';
	return os;
}

template<typename T, bool select>
struct select_container {
	std::ostream &os;

	select_container(std::ostream &os) : os(os) {
	}

	std::ostream& operator()(T const &t) {
		WithDelimiterPrinter<typename T::value_type> printer(os);
		os << demangle(typeid(T).name()) << '{';
		std::for_each(t.begin(), t.end(), printer);
		return os << '}';
	}
};

template<typename T>
struct select_container<T, false> {
	std::ostream &os;

	select_container(std::ostream &os) : os(os) {
	}

	std::ostream & operator()(T const& t) {
		// look for std::pair. a future with tuple might be useful as well, but not now.
		return print_pair(os, t); // here a simple template function overload works.
	}
};

template<typename T>
struct select_built_in_shift_if<T, false> {
	std::ostream &os;

	select_built_in_shift_if(std::ostream &ros) : os(ros) {
	}

	std::ostream & operator()(T const& t) {
		// if no operator<< is found, try if it is a container or std::pair
		return select_container<T,
				to_string_detail::has_begin_end_const_member<T>::value>(os)(t);
	}
};

#define HELPER_MEM_FUNS std::string getTrace() const {\
		return trace;\
	}\
	std::ostream& printTo(std::ostream& os) const {\
		return os << trace;\
	}

#if defined(USE_STD11)
struct call {
	template<typename ... Param>
	call(std::string const& funSig, Param const& ... params) {
		record(funSig, params ...);
	}

	HELPER_MEM_FUNS
private:
	template<typename Head, typename ...Tail>
	void record(Head const& head, Tail const& ...tail) {
		std::ostringstream oss;
		toStream(oss, head);

		if (sizeof...(tail)) {
			oss << ",";
		}

		trace.append(oss.str());
		record(tail ...);
	}

	void record() {
	}

	std::string trace;
};
#else
#if !defined(MAX_NUM_OF_PARAMETERS)
# define MAX_NUM_OF_PARAMETERS 10
#endif

template<typename T>
std::string toString(T const& t) {
	std::ostringstream os;
	toStream(os, t);
	return os.str();
}

#define PRINT_CALL(z, n, name) << "," << toString(name ## n)

struct call {
#define MAKE_CALL(z, n, unused) \
	template <typename T BOOST_PP_ENUM_TRAILING_PARAMS(n, typename T)> \
		call(T t BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, T, t)) { \
			std::ostringstream oss; \
			oss << toString(t) BOOST_PP_REPEAT(n, PRINT_CALL, t); \
			trace.append(oss.str()); \
		}

	BOOST_PP_REPEAT(MAX_NUM_OF_PARAMETERS, MAKE_CALL, ~)

	HELPER_MEM_FUNS
private:
	std::string trace;
};
#endif

typedef std::vector<call> calls;

inline std::ostream& operator<<(std::ostream& os, call const& c) {
	return c.printTo(os);
}

struct CallsPrinter: std::unary_function<call, void> {
	CallsPrinter(std::ostream& out) : os(out) {
		os << "[\n";
	}
	void operator()(call const& c) {
		os << c << "\n";
	}
	std::ostream& close() {
		return os << "]";
	}
private:
	std::ostream& os;
};

template<typename Container>
inline std::ostream& printTo(std::ostream& os, Container const& c) {
	return std::for_each(c.begin(), c.end(), CallsPrinter(os)).close();
}

inline std::ostream& operator<<(std::ostream& os,
		std::multiset<call> const& container) {
	return printTo(os, container);
}

inline std::ostream& operator<<(std::ostream& os, calls const& container) {
	return printTo(os, container);
}

inline bool operator==(call const& lhs, call const& rhs) {
	return lhs.getTrace() == rhs.getTrace();
}

inline bool operator!=(call const& lhs, call const& rhs) {
	return !(lhs == rhs);
}

inline bool operator<(call const& lhs, call const& rhs) {
	return lhs.getTrace() < rhs.getTrace();
}

inline bool equalsAnyOrder(calls const& expected, calls const& actual) {
	return std::multiset<call>(expected.begin(), expected.end())
			== std::multiset<call>(actual.begin(), actual.end());
}
}

#define SORTED_CONTAINER(calls)\
		(std::multiset<mockator::call>(calls.begin(), calls.end()))

#define ASSERT_ANY_ORDER(expected,actual)\
	ASSERT_EQUAL(SORTED_CONTAINER(expected), SORTED_CONTAINER(actual))

namespace mockator {
size_t reserveNextCallId(std::vector<calls> & allCalls) {
	size_t counter = allCalls.size();
	allCalls.push_back(calls());
	return counter;
}
}

#if !defined(USE_STD11)
# define USE_BOOST_NS using namespace boost::assign;
#else
# define USE_BOOST_NS
#endif

#define USE_MOCKATOR_NS using mockator::call;\
	using mockator::calls;

#define INIT_MOCKATOR() USE_MOCKATOR_NS\
	USE_BOOST_NS

#define ASSERT_MATCHES(expected,actual) mockator::assertAllMatching((expected),(actual))

namespace mockator {

struct RegexMatchingFailure: std::exception {
	std::string reason;

	RegexMatchingFailure(std::string const& r) :
			reason(r) {
	}

	~RegexMatchingFailure() throw () {
	}

	char const* what() const throw () {
		return reason.c_str();
	}
};

void assertAllMatching(calls const& expected, calls const& actual) {
	if (expected.size() != actual.size()) {
		throw RegexMatchingFailure(
				"Number of actual calls does not match expectations");
	}

	for (calls::size_type i = 0; i != expected.size(); ++i) {
		std::string expectedTrace = expected[i].getTrace();
		std::string actualTrace = actual[i].getTrace();

		if (expectedTrace[0] == '^') {
			std::string expectedRegex = expectedTrace.substr(1);
			boost::regex r(expectedRegex, boost::regex::basic);

			if (!boost::regex_match(actualTrace, r)) {
				std::string desc = expectedRegex + " did not match "
						+ actualTrace;
				throw RegexMatchingFailure(desc);
			}
		} else if (expectedTrace != actualTrace) {
			std::string desc = expectedTrace + " not equal to " + actualTrace;
			throw RegexMatchingFailure(desc);
		}
	}
}
}

#endif
