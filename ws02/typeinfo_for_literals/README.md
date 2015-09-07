This program will give the answers to the interactive lecture
by printing the types of literals and its value.

**NB:** It uses GCC-specific compiler intrinsics to provide a user-readable
typename, i.e., the `typeinfo::name()` function would return "i" for an "int", as
defined in the Itanium ABI used by this compiler. It also works with Clang, since
it uses the same ABI and API. The MS C++ compiler will provide a user-readable
typename string by just calling `typeinfo::name()`