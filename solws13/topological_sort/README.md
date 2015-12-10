These are some test cases for the slow and primitive implementation of topological sorting.

The problem solved is described as follows:

**Topological Sort**

Solve the exercise from the OO module in C++ using (smart) pointers to build the graph of objects.

Read dependencies from a file, 
where the first string provides the current module name 
and the following strings its pre-requisites. 
The file is not sorted, so that modules might be pre-requisites, before you know what pre-requisites theses modules have. Create a "node" class with a string and appropriate container with shared_ptr to this class. input.txt:
```
DB1 OO
DB2 DB1
Math
OO
AD1 OO
CPI OO Math
Thesis DB2 SE2 UI2
SE1 AD1 CPI DB1
SE2 DB1 SE1 UI1
UI1 AD1
UI2 UI1
```
output:
```
1: Math OO
2: DB1 AD1 CPI
3: DB2 SE1 UI1
4: SE2 UI2
5: Thesis
```
Build a dependency graph, where each node has a container of shared_ptr to nodes it depends on. Keep a dictionary of all nodes for easy check if a node with a given name was already produced
Produce an output that assigns a schedule, where each semester only modules are selected, where all pre-requisites are fulfilled. Start with those nodes that do not have a pre-requisite.

_NOTE_

provide a separate main() where you can pass the filename as a command line argument.
* Do not produce a memory leak!
* Do not instantiate objects representing the same lecture twice!
* Do not start with your Java code from last year!
* Write unit tests for your functions!
_Optional::_
* Test your code also with the large dependency file: LargeCatalogue.txt
* measure timing as follows (using `#include <chrono>`):
```
    auto start=std::chrono::system_clock::now();
    // do your stuff
    std::chrono::duration<double> delta=std::chrono::system_clock::now()-start;
    out << delta.count() << "s time\n";
```
