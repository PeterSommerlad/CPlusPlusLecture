#ifndef SRC_FIBO_H_
#define SRC_FIBO_H_

template <int n>
struct Fibo {
	static_assert(n>=2,"Fibo must be called with a positive number");
    static int const value=Fibo<n-1>::value+Fibo<n-2>::value;
};

template<>
struct Fibo<0> {
	static int const value=0;
};
template<>
struct Fibo<1> {
	static int const value=1;
};


#endif /* SRC_FIBO_H_ */
