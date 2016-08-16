#include "iterator.h"
#include <vector>
#include <list>

int main(){
	std::vector<int> v{3,1,4,1,5,9,2,6};
	mysort(v.begin(),v.end());
	std::list<int> l{3,1,4,1,5,9,2,6};
	mysort(begin(l),end(l)); // concept check fails
//	std::sort(l.begin(),l.end()); // horrible compile error
}
