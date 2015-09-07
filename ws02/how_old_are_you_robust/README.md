This example program shows a more robust way to enter integers 
from a `std::istream` by reading in a string first and then
parsing it either through a `std::istringstream` checking for
its failuere or via 
`std::stoi()` which will cause an exception if it can not convert.