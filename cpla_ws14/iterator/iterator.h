#include <iterator>
#include <algorithm>
template <typename ITER>
using Value_type=typename std::iterator_traits<ITER>::value_type;
template <typename ITER>
using IterCategory=typename std::iterator_traits<ITER>::iterator_category;

template <typename ITER>
concept bool Iterator() {
return requires(ITER it, ITER end){
	IterCategory<ITER>();
	{ *it++ } -> Value_type<ITER>;
	{ it != end } -> bool;
};
}
template <typename OITER>
concept bool OutputIterator() {
return requires(OITER out){
	{IterCategory<OITER>()}->std::output_iterator_tag;
	*out = Value_type<OITER>();
	++out;
};
}
template <Iterator ITER>
concept bool ForwardIterator() {
return requires(ITER it, ITER end){
	{ std::iterator_traits<ITER>::iterator_category() } -> std::forward_iterator_tag;
};
}
template <ForwardIterator ITER>
requires OutputIterator<ITER>()
concept bool WritableRandomAccessIterator() {
return requires(ITER it) {
	{ it[0] } -> Value_type<ITER>;
};
}

template <WritableRandomAccessIterator ITER> 
void mysort(ITER b, ITER e) {
	std::sort(b,e);
}

