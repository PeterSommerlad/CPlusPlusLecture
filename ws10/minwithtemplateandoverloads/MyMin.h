#ifndef MYMIN_H_
#define MYMIN_H_
namespace MyMin{
template <typename T>
T const& min(T const& a, T const& b){
	return (a < b)? a : b ;
}
template <typename T>
T const * min(T const* a, T const* b){
	return (*a < *b)? a : b ;
}
char const * min(char const* a, char const* b);

}

#endif /*MYMIN_H_*/
