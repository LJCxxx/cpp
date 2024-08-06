# cpp
Just some basic templates.\
**List.h** is a doubly linked list. demonstrates class composition and operator overloading; however, as a node-based structure, it typically results in poor memory access patterns and is generally less recommended except for use in trees or graphs. Other linear data structures with contiguous memory alignment, such as traditional C arrays, std::vector, or even std::valarray, are generally preferred for better memory access patterns.\
**lambdas.cpp** uses variadic function template for lambda composition(for single and multi arguments), a functional programming (FP) concept where functions are composed to create higher-order functions. Some of the functions have the consteval/constexpr specifier. These specifiers indicate to the compiler to evaluate the functions at compile time, and the function call is replaced with the return value.\
**alloc.cpp** is a simple implementation of memory preallocation, a data oriented design technique aimed at reducing/eliminating runtime memory allocation and keeping data compact.

<br/><br/>sources:\
Marius Bancila, Modern C++ Programming Cookbook. Packt Publishing Ltd, 2024.\
M. T. Goodrich, D. M. Mount, and R. Tamassia, Data structures and algorithms in C++. Hoboken, N.J.: John Wiley & Sons, Cop, 2011.
