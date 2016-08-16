#include <utility>
#include <stdexcept>
// std::exchange is not constexpr...
template <typename T, typename V>
constexpr auto exchange(T& var,V && val){
	T const old = std::move(var);
	var = std::forward<V>(val);
	return old;
}

constexpr auto fibo(int n){
	extern char const * const fibo_must_not_be_called_at_run_time;
	size_t f0{0},f1{1};
	if (n < 0) throw std::logic_error{fibo_must_not_be_called_at_run_time};
	while(n-->0){
		f0=exchange(f1,f1+f0);
	}
	return f0;
}

// "cheating version"
template <int n>
constexpr auto fibo_v=fibo(n);


template <size_t n>
constexpr size_t fibo1_v{fibo1_v<n-1>+fibo1_v<n-2>};
template<>
constexpr size_t fibo1_v<0u>{0u};
template<>
constexpr size_t fibo1_v<1u>{1u};

constexpr size_t five=fibo1_v<4u>;

static_assert(0==fibo1_v<0>,"fibo(0)");
static_assert(1==fibo1_v<1>,"fibo(1)");
static_assert(1==fibo1_v<2>,"fibo(2)");
static_assert(2==fibo1_v<3>,"fibo(3)");
static_assert(3==fibo1_v<4>,"fibo(4)");
static_assert(1836311903==fibo1_v<46>,"fibo(46)");




