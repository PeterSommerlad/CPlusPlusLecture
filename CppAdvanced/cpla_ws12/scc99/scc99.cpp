#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <cassert>

using namespace std;
using namespace std::chrono;
constexpr size_t POOL_SIZE = 4;

// Allow up to 4 active threads
array<thread, POOL_SIZE> pool;
std::mutex poolmutex{};
using guard=std::lock_guard<std::mutex>;
// Example 'worker' -- would in practice
// perform some, potentially slow, calculation
void worker()
{
	using namespace std::chrono_literals;
    this_thread::sleep_for(150ms);
    cout << "Worker done\n";
}

auto find_in_pool(thread::id id=thread::id{}){
	guard guard{poolmutex};
	return find_if(begin(pool),end(pool),
			[id](thread const &thr)
			    { return thr.get_id() == id; }
);
}


// Launch the thread functoid 't' in a new
// thread, if there's room for one
template <typename T>
bool launch(T t)
{
  auto it = find_in_pool();
  if (it == pool.end())
  {
    // everyone is busy
    return false;
  }
  {
	  guard lk{poolmutex};

	  *it = thread([](auto && t) {
		  t();
		  auto self=find_in_pool(this_thread::get_id());
		  if (self != end(pool)) {
			  guard lk{poolmutex};
			  self->detach();
			  cout << "Ending thread #"
					  << end(pool)-self << "\n";
			  assert(self->get_id() != this_thread::get_id());
		  } else {
			  cerr << "Oops, not found: "<< this_thread::get_id()<<endl;
		  }
	  }, t);
  }
    return true;
}

int main()
{
  while (launch(worker))
  {}

  // And run one in this thread
  // as an example of what we do
  // when the pool is full
  worker();

  { guard lk{poolmutex};
  for (auto & it : pool)
  {
    thread thread;
    swap(thread, it);
    if (thread.joinable())
    {
      cout << "Awaiting thread #"
        << (&it - &*pool.begin()) << "\n";
      thread.join();
    }
  }
  }
  cout << "All done\n";
}




