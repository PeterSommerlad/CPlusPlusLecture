The header file `ratio_operators.h` for the operations and functionality for working with rational numbers based on std::ratio
for the following exercise is missing.

##Exercise: constexpr operator for arithmetic and comparisons for `std::ratio<N,D>`

Implement the normal arithmetic operators for values of std::ratio<N,D> types an return the correct resulting type using 
`std::ratio_add<>` etc.

Do the same for the comparison operators `std::ratio_less<R1,R2>` etc.

Make sure the overloaded operator template functions are only considered for arguments of types 
instantiated from `std::ratio` by providing a meta-function, e.g., through a variable template `bool is_ratio<R>`.

Provide also UDL suffixes `_num _den` in the namespace `ratio_literals`, so that
```C++
  static_assert(1_num/3_den == std::ratio<1,3>{}, "ratio literals OK"); 
```
compiles, when you are
```C++
  using namespace ratio_literals;
``` 
