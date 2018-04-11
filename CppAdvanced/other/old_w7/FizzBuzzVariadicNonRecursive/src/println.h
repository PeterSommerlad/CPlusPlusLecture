/*
 * println.h
 *
 *  Created on: 18.09.2015
 *      Author: sop
 */

#ifndef PRINTLN_H_
#define PRINTLN_H_
#include <ostream>

void println(std::ostream &out) ;

template<typename Head, typename... Tail>
void println(std::ostream &out, Head const& head, Tail const& ...tail) {
	out << head;
	if (sizeof...(tail)) {
		out << ", ";
		println(out,tail...); //recurse on tail
	} else {
		out<< '\n';
	}
}

inline
void println(std::ostream &out) {
	throw "never called";
}




#endif /* PRINTLN_H_ */
