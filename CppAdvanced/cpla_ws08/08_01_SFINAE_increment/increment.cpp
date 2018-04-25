namespace v1{
unsigned increment(unsigned i) {
  return i++;
}

template<typename T>
T increment(T value) {
  return value.increment();
}

int main1() {
//  return increment(42); // error: reference base type 'int' is not a structure or union
}
}
namespace v2{
template<typename T>
auto increment(T value) -> decltype(value.increment()) {
  return value.increment();
}

int main2(){
//	return increment(42); // note: candidate template ignored: substitution failure
}
}
namespace v3{

template<typename T>
auto increment(T value) ->
    decltype(value.increment()) {
  return value.increment();
}
template<>
unsigned increment<int>(unsigned i) {
  return i++;
}

}
int main() {
  using namespace v3;
  return increment(42);
}





















