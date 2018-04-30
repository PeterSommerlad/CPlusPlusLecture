#include <future> // defines async and future
#include <iostream>
#include <chrono>
unsigned long long fibo_def(unsigned long long n){
	if (n < 1) return 0;
	if (n < 2) return 1;
	auto f1 = std::async(fibo_def,n-1); // obtain future, eventually start thread
	auto f2 = std::async(fibo_def,n-2); // obtain future, eventually start thread
	return f1.get() + f2.get(); // use future's result
}
unsigned long long fibo_def_async(unsigned long long n) {
	if (n < 1)
		return 0;
	if (n < 2)
		return 1;
	auto f1 = std::async(std::launch::async, fibo_def_async, n - 1);
	auto f2 = std::async(std::launch::async, fibo_def_async, n - 2);
	auto result = f1.get() + f2.get();
	return result; // use future's result
}
unsigned long long fibo_def_deferred(unsigned long long n) {
	if (n < 1)
		return 0;
	if (n < 2)
		return 1;
	auto f1 = std::async(std::launch::deferred, fibo_def_deferred, n - 1);
	auto f2 = std::async(std::launch::deferred, fibo_def_deferred, n - 2);
	auto result = f1.get() + f2.get();
	return result; // use future's result
}

int main(int argc){
	unsigned long long n=20; // argc+3 // 20 crashes fibo_def_async --> too many threads?
	using Clock=std::chrono::high_resolution_clock;
    using msec=std::chrono::milliseconds;
    Clock::time_point t0 = Clock::now(); // standard millisecond timing
    auto fibn=fibo_def(n);
	Clock::time_point t1 = Clock::now();
    msec ms = std::chrono::duration_cast<msec>(t1 - t0);
    std::cout <<"fibo_def("<<n<<") = " << fibn<<" :" << ms.count() << "ms\n";
}

// ridiculous example:

void someAsyncStuff();

void foo() {
	std::async(std::launch::async, someAsyncStuff);
	std::async(std::launch::async, someAsyncStuff);
	std::async(std::launch::async, someAsyncStuff);
}
