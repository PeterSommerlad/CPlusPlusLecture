#include "calc.h"

int calc(int l, int r, char op) {
	switch(op){
	case '+': return l+r;
	case '-': return l-r;
	case '*': return l*r;
	case '/': return (r!=0)?l/r:0;
	case '%': return (r!=0)?l%r:0;
	default: return 0;
	}
}
