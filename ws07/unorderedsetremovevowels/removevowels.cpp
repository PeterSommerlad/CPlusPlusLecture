#include <unordered_set>
#include <iostream>
#include <iterator>
#include <algorithm>
int main(){
  std::unordered_set<char> const vwl{'a','e','i','o','u'};
  using in=std::istreambuf_iterator<char>;
  using out=std::ostreambuf_iterator<char>;
  remove_copy_if(in{std::cin},in{},out{std::cout},
		         [&](char c){return vwl.count(c);});
}
