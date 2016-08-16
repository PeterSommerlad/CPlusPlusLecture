#include <atomic>
#include <iostream>
template <typename ATOM>
void printIsLockFree(std::ostream &out, std::string const &which
		            , ATOM &atomic){
	out << std::boolalpha <<"atomic<"
			<< which << "> is_lock_free = "
			<< atomic.is_lock_free()<<'\n';
}
struct X{
	char a[sizeof(void*)];
}; // must be trivially copyable and on my g++ not too big
#define PRINT(type) { std::atomic<type> const x{}; \
	                  printIsLockFree(std::cout,#type,x);}
int main() {
	using std::cout;
	using std::endl;
	PRINT(bool);
	PRINT(int);
	PRINT(double);
	PRINT(int64_t);
	PRINT(X);
}
