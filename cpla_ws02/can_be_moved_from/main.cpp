#include <utility>


struct S {};

void foo(S && s) {
	//do something fancy with s
}

int main()
{
  S s{};
  foo(S{}); 			//From S{} can be moved
  //foo(s);   			//From s cannot be moved directly
  foo(std::move(s)); 	//std::move converts s into something movable
}
