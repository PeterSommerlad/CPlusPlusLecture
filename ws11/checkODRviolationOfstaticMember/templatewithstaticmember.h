#ifndef TEMPLATEWITHSTATICMEMBER_H_
#define TEMPLATEWITHSTATICMEMBER_H_
template <typename T>
struct staticmember{
	static int dummy;
};
template <typename T>
int staticmember<T>::dummy{sizeof(T)};
#endif /* TEMPLATEWITHSTATICMEMBER_H_ */
