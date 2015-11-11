This exercise shows bad function design, 
where a function computes a value and has a side effect on its argument.

don't do it at home.

a more efficient solution could use transform with a lambda and counting
the occurences where a change is really necessary. this would iterate 
the string only once.