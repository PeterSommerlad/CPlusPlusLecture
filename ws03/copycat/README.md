This example demonstrates the use of the `istreambuf_iterator` and `ostream_iterator` types 
for reading and writing standard output. Since `istreambuf_iterator` uses the `get(char)` member function
of `std::istream` it will read all characters and not skip whitespace on input.

*CAUTION* Do not run this within the Cevelop Console on non-Windows operating systems, 
unless you have a very recent version of Cevelop, because
Eclipse has a bug with the EOF (Ctrl-D) handling in its console that only got fixed recently.