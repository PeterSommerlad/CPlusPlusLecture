This is the project diretory for the 3rd Testat exercise

##TESTAT-3: BoundedQueue with timed operations

Write a `template <typename T, typename M=std::mutex, typename CV=std::condition_variable> class BoundedQueue`
template class that provides the functions
```C++
push(T) - both copy and move
T pop()
bool try_push(T const &)
bool try_pop(T&)
bool try_push_for(T const &, std::chrono::duration)
bool try_pop_for(T &, std::chrono::duration)
//we do not ask for _until versions
size(), empty(), full()
```
plus copy/move operations

Use the mechanisms from your `BoundedBuffer` to allow move-only and non-default-constructible template argument types.
You can also copy parts of the code and add the required synchronization.
Use the default template arguments of `M` and `CV` `std::mutex` and `std::condition_variable`
for synchronization by employing the template parameters M and CV. 
This allows test cases to substitute them for checking if synchronization happens in the single-threaded case 
(Strategized Locking Pattern).

Ensure that exceptions will not keep the mutex locked. Remember what standard wrapper classes you can use.

Please also answer the following questions when handing in your header file:
* Why can't be use the `front()` and `back()` member functions from `BoundedBuffer`?
* Why doesn't it make sense to provide iterators for `BoundedQueue`?
* Can you suggest an alternative means for observing the `BoundedQueue` content?
* Why is `pop()` returning a value by value and not `void` as in `BoundedBuffer`?
