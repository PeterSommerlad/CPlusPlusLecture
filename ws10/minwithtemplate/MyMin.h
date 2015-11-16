#ifndef MYMIN_H_
#define MYMIN_H_
namespace MyMin{
template <typename T>
T const& min(T const& a, T const& b){
	return (a < b)? a : b ;
}
}
#endif /*MYMIN_H_*/
