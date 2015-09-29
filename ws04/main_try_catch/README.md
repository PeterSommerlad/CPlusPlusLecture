C++ allows try-catch blocks for function bodies.

This implies, even main() can have such a try-catch function body.

It looks unusual but is completely OK and could even provide 
a "graceful death" from a program throwing exceptions internally.