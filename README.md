# cpp
Just some basic templates.\
<br/>
**List.h** is a doubly linked list. demonstrates class composition and operator overloading; however, as a node-based structure, it typically results in poor memory access patterns and is generally less recommended except for use in trees or graphs. Other linear data structures with contiguous memory alignment, such as traditional C arrays, std::vector, or even std::valarray, are generally preferred for better memory access patterns.\
<br/>
**lambdas.cpp** uses variadic function template for lambda composition(for single and multi arguments), a functional programming (FP) concept where functions are composed to create higher-order functions. Some of the functions have the consteval/constexpr specifier. These specifiers indicate to the compiler to evaluate the functions at compile time, and the function call is replaced with the return value.\
<br/>
**alloc.cpp** is a wrapper around malloc, serving as a memory management abstraction rather than a full-fledged custom allocator. It provides a basic implementation of memory preallocation and sandboxing—a data-oriented design technique aimed at reducing or eliminating runtime memory allocation and keeping data compact.

<br/><br/>sources:\
Marius Bancila, Modern C++ Programming Cookbook. Packt Publishing Ltd, 2024.\
M. T. Goodrich, D. M. Mount, and R. Tamassia, Data structures and algorithms in C++. Hoboken, N.J.: John Wiley & Sons, Cop, 2011.
