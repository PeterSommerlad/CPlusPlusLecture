#include <atomic>
#include <thread>
#include <array>
#include <iostream>
using namespace std::this_thread;

constexpr size_t max_count{10};
constexpr size_t max_threads{5};
constexpr std::memory_order order=std::memory_order_relaxed;//std::memory_order_seq_cst; //std::memory_order_relaxed

// latch
std::atomic<bool> startflag{};
// subject to load/stores:
std::atomic<int> x{};
std::atomic<int> y{};
std::atomic<int> z{};

struct values_read{
	int x,y,z;
};
void waitForStartFlag(){
	while(!startflag) yield();
}
void increment(std::atomic<int>&x_or_y, std::array<values_read,max_count> &val){
	waitForStartFlag();
	for(size_t i=0; i < max_count ; ++i){
		val[i].x = x.load(order);
		val[i].y = y.load(order);
		val[i].z = z.load(order);
		x_or_y.store(i+1,order);
		yield();
	}
}
void read(std::array<values_read,max_count> &val){
	waitForStartFlag();
	for(size_t i=0; i < max_count ; ++i){
		val[i].x = x.load(order);
		val[i].y = y.load(order);
		val[i].z = z.load(order);
		yield();
	}
}
void print(std::array<values_read,max_count> const &val){
	for(auto const &elt:val){
		std::cout << "("<<elt.x<<","<<elt.y<<","<<elt.z<<"),";
	}
	std::cout << '\n';
}

int main() {
	std::array<std::array<values_read,max_count>,max_threads> values{};

	std::thread inc1{increment,std::ref(x),std::ref(values[0])};
	std::thread inc2{increment,std::ref(y),std::ref(values[1])};
	std::thread inc3{increment,std::ref(z),std::ref(values[2])};
	std::thread read1{read,std::ref(values[3])};
	std::thread read2{read,std::ref(values[4])};

	startflag=true; // open latch
	inc1.join();inc2.join();inc3.join();read1.join();read2.join();

	for (auto const &row:values){
		print(row);
	}
}
