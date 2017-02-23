#ifndef INCREMENT_H_
#define INCREMENT_H_

#include <limits>
#include <stdexcept>


//1. functional increment
inline int increment_by_value(int const value) {
	return value + 1;
}

//2. side-effect increment
//inline void increment(int & value) {
//	value++;
//}

//3. safe side-effect increment
//inline void increment(int & value) {
//	if (value == std::numeric_limits<int>::max()) {
//		throw std::overflow_error{"cannot increment max value"};
//	}
//	value++;
//}

//4. arbitrary types
//template<typename T>
//void increment(T & value) {
//	if (value > std::numeric_limits<T>::max() - 1) {
//		throw std::overflow_error{"cannot increment max value"};
//	}
//	value++;
//}

//5. overload for unsigned long long to allow increment of max value
//Does not need to be a template specialization
//inline void increment(unsigned long long & value) {
//	value++;
//}

//6. predicate with specialization as variable template
//template<typename T>
//constexpr bool allow_overflow { false };
//
//template<>
//constexpr bool allow_overflow<unsigned short> { true };
//
//template<>
//constexpr bool allow_overflow<unsigned> { true };
//
//template<>
//constexpr bool allow_overflow<unsigned long> { true };
//
//template<>
//constexpr bool allow_overflow<unsigned long long> { true };
//
//template<>
//constexpr bool allow_overflow<unsigned char> { true };
//
//template<typename T>
//void increment(T & value, T const limit = std::numeric_limits<T>::max()) {
//	if (!allow_overflow<T> && value > limit - 1) {
//		throw std::overflow_error{"cannot increment max value"};
//	}
//	value++;
//}

//6. predicate with specialization as class template
//template<typename T>
//struct allow_overflow {
//	static constexpr bool value { false };
//};
//
//template<>
//struct allow_overflow<unsigned> {
//	static constexpr bool value { true };
//};
//...

//6. predicate with specialization as function template
//template<typename T>
//bool allow_overflow() {
//	return false;
//}
//
//template<>
//bool allow_overflow<unsigned>() {
//	return true;
//}
//...

//7. & 8. simplified predicate and default parameter
template<typename T>
constexpr bool allow_overflow { std::numeric_limits<T>::is_integer && std::is_unsigned<T>::value };

template<typename T>
void increment(T & value, T const limit = std::numeric_limits<T>::max()) {
	if (!allow_overflow<T> && value > limit - 1) {
		throw std::overflow_error{"cannot increment max value"};
	}
	value++;
}

#endif /* INCREMENT_H_ */
