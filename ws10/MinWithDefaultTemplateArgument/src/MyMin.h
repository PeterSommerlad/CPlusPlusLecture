#ifndef MYMIN_H_
#define MYMIN_H_

namespace MyMin{

template <typename T, typename U = T>
auto min(T const& a, U const& b)->decltype(a<b?a:b){
	return (a < b)? a : b ;
}
template <typename T,typename U=T>
void min(T * a, U * b)=delete;

char const * min(char const* a, char const* b);

}
namespace MyMinBad{

template <typename T, typename U >
T min(T const& a, U const& b){
	return (a < b)? a : b ;
}
template <typename T,typename U=T>
void min(T * a, U * b)=delete;

char const * min(char const* a, char const* b);

}

#endif /*MYMIN_H_*/
