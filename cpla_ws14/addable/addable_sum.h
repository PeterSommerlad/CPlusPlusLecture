template <typename ADD, typename ADD2=ADD>
concept bool Addable(){
	return requires(ADD a, ADD2 b){
		a+b;
	};
}
template < typename ADD, typename ADD2=ADD>        
requires Addable<ADD, ADD2>()
ADD add(ADD a, ADD2 b) 
{
        return a+b;
}
template <typename ADD>
concept bool Addable1(){
	return requires(ADD a, ADD b){
		a+b;
	};
}
template < Addable1 ADD>
ADD add1(ADD a, ADD b) 
{
        return a+b;
}

#include <iterator>
template <typename ITER>
using Value_type=typename std::iterator_traits<ITER>::value_type;

template <typename ITER>
concept bool Iterator() {
return requires(ITER it, ITER end){
	typename std::iterator_traits<ITER>::iterator_category;
	{ *it++ } -> Value_type<ITER>;
	{ it != end } -> bool;
};
}

template <Iterator ITER, typename T>
requires Addable<T, Value_type<ITER>>()
T sum(ITER b, ITER e, T start){
	while(b != e) start = start + *b++;
	return start;
}

