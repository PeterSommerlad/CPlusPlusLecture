#ifndef MYMAX_H_
#define MYMAX_H_
namespace MyMax{
template <typename T>
T max(T a, T b){
	return a < b ? b : a;
}

}

#endif /* MYMAX_H_ */
