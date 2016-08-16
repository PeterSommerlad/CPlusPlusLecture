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
int main(int argc, char **argv){
	if (argc < 2 || atoi(argv[1]) <1) {
		std::cout<< "Usage: "<< argv[0] << " number\n";
		exit(1);
	}
	unsigned long long n=std::strtoull(argv[1],nullptr,10);
	using Clock=std::chrono::high_resolution_clock;
    using msec=std::chrono::milliseconds;
    Clock::time_point t0 = Clock::now(); // standard millisecond timing
    auto fibn=fibo_def(n);
	Clock::time_point t1 = Clock::now();
    msec ms = std::chrono::duration_cast<msec>(t1 - t0);
    std::cout <<"fibo_def("<<n<<") = " << fibn<<" :" << ms.count() << "ms\n";
}
