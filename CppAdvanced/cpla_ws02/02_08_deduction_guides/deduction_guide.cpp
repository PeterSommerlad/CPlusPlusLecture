#include <vector>
#include <iterator>

template<typename T>
struct Box {
    Box(T content)
      : content{content}{}
    T content;
};

template<typename T>
struct BoxWithDeduction {
	template<typename CT>
	BoxWithDeduction(CT content)
		: content{content}{}
	T content;
};

template<typename CT>
BoxWithDeduction(CT) -> BoxWithDeduction<CT>;


template<typename T>
struct BoundedQueue {
  template<typename Iter>
  BoundedQueue(Iter begin, Iter end){}
  //...
};

template<typename Iter>
BoundedQueue(Iter, Iter) -> BoundedQueue<typename std::iterator_traits<Iter>::value_type>;

int main() {
  Box<int> b0{0}; //Before C++17
  Box      b1{1}; //Since C++17

  BoxWithDeduction b{1};

  std::vector<int> ints{1, 2, 3};
  BoundedQueue queue{std::begin(ints), std::end(ints)};
}
