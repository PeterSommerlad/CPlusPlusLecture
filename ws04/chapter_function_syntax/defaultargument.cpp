#include "defaultargument.h"
void incr(int &var,unsigned delta){
	var += delta;
}




void use_incr(){
	int i{42};
	incr(i); // 43
	incr(i,2); // 45
}
