#ifndef MYMAX_H_
#define MYMAX_H_
#include <type_traits>
namespace MyMax{
template <typename T,typename U>
typename std::common_type<T const &, U const &>::type
max(T const &a, U const & b){
	return a < b ? b : a;
}

}

#endif /* MYMAX_H_ */
