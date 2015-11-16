#ifndef MYMIN_H_
#define MYMIN_H_
#include <type_traits>
namespace MyMin{
#if 0
template <typename T, typename U = T>
typename std::common_type<T const &,U const &>::type
min(T const& a, U const& b){
	return (a < b)? a : b ;
}
#endif

template <typename T, typename U = T>
auto min(T const& a, U const& b)->decltype(a<b?a:b){
	return (a < b)? a : b ;
}
template <typename T,typename U=T>
void min(T * a, U * b)=delete;

char const * min(char const* a, char const* b);

}

#endif /*MYMIN_H_*/
