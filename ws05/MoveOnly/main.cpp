#include <iostream>
#include <set>
struct MoveOnly
{
   MoveOnly() = default;
   MoveOnly(MoveOnly&&) {
       std::cout << "Move constructor called\n";
   }
   //MoveOnly(const MoveOnly&) = delete; // implicitly deleted
};
void bar(MoveOnly const *){}
void f(MoveOnly) { std::cout << "f(MoveOnly) called\n"; }
int main1(){
   f( MoveOnly{} ); // rvalue temporary
   std::cout << "moving lvalues:\n";
   MoveOnly mv{}; // lvalue
   MoveOnly const &cr=MoveOnly{};
 //  f(std::move(cr)); // doesn't compile
//f(mv); // doesn't compile, lvalue cannot be passed
   f(std::move(mv)); // make an rvalue from lvalue
   bar(&mv);
   bar(&cr);
}


// check if decltype([]{}) can be used as template argument for set

template<typename T, typename C>
auto make_set(C c) ->std::set<T,C>{
	return std::set<T,C>{c}; // cannot instantiate without c
	// lambda's default ctor=delete
}

int main(){
	auto s=make_set<int>([](int x, int y){return y<x;});
	s.insert({2,1,4,2,6,0});
	for (auto x:s) std::cout << x <<", ";

}
