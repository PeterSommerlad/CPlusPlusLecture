#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono;
static const int POOL_SIZE = 4;

// Allow up to 4 active threads
array<thread, POOL_SIZE> pool;

// Example 'worker' -- would in practice
// perform some, potentially slow, calculation
void worker()
{
  this_thread::sleep_for(
    milliseconds(rand() % 1000));


  cout << "Worker done\n";
}

// Launch the thread functoid 't' in a new
// thread, if there's room for one
template <typename T>
bool launch(T t)
{
  auto it = find_if(pool.begin(), pool.end(),
    [](thread const &thr)
    { return thr.get_id() == thread::id(); }
  );
  if (it == pool.end())
  {
    // everyone is busy
    return false;
  }
  *it = thread([=]()
  {
    t();
    thread self;
    swap(*it, self);
    self.detach();
    cout << "Ending thread #"
      << (it - pool.begin()) << "\n";
  });
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
  cout << "All done\n";
}




