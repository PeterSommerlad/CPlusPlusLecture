#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
template<typename ITER>
void show(ITER const &b, ITER e, std::ostream& os) {
	std::ostream_iterator<int> out(os,", ");
	copy(b, e, out);
	os << '\n';
}
int main(){
  std::vector<int> const v{3,1,4,1,5,9,2,6};
  std::vector<int> const s{4,1,5,6};
  using std::cout;
  show(cbegin(v),cend(v),cout);
  show(cbegin(s),cend(s),cout);
  auto
    start=search(cbegin(v),cend(v),cbegin(s),cend(s)-1);
  show(cbegin(v),start,cout);
  if (distance(start,cend(v))>= distance(cbegin(s),cend(s))){
	  auto p=mismatch(start,cend(v),cbegin(s));
  	  show(p.first,cend(v),cout);
  	  show(p.second,cend(s),cout);
  } else {
	  auto p=mismatch(cbegin(s),cend(s),start);
  	  show(p.first,cend(s),cout);
  	  show(p.second,cend(v),cout);
  }
}
