This is a solution to exercise "Function-Value Table"

Create a library with a function printFunctionTable that takes an ostream, a beginning and end value of type double, a number of steps, and a function as arguments. The function will produce a table of function values as follows by dividing the range given into n steps and prints the function results as follows: (start=1.0, end=3.0, steps=3, f(x) = [](double x){return x*x;})

`x    1.0 2.0 3.0  `

`f(x) 1.0 4.0 9.0  `

You might use a loop for the solution, or store the n used x values in a std::vector<double> first, by using algorithm generate(_n).

See the corresponding test cases for usage.