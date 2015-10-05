This example library demonstrates operator overloading in a way, 
so that the class becomes a "Literal Type" and is usable for compile-time computations.

Note the use of operator overloading and constexpr.

Because Boost.operators are not (yet) constexpr compatible, 
the code is incomplete wrt to the defined operators.

Completion to include full set of arithmetic and relational operators is left as an exercise.

Test cases should be extended using static_assert to really check for compile-time computation.