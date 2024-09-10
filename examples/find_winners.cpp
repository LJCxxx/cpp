// find_winners(f, m, n) reads 3 inputs:
// factor digit f [1-9]
// must-have digit [1-9]
// number of participants [1-n]
// e.g. find_winners(3,5,100) has 6 winners {15,45,51,54,57,75}
//
// ====================================================
//
// While find_winners is a straightforward problem typically solvable with a loop,
// a couple of conditions, and a counter, a more modular and functional approach
// can be taken with lambdas and c++20 ranges. The predicate function
// can be composed with lambdas—one for the factor check and another for the
// must-have digit. iota generates the 1 to n range. Then, the predicate function is 
// applied by piping filter to iota. Finally, distance returns the number of winners.
// The approach can be easily modified to return the actual list of winners.
//
// This version emphasizes modularity by highlighting how each part of the solution
// can be composed and reused.

#include <string>
#include <ranges>
#include <iostream>

auto find_winners(int f, int m, int n) {
  auto factor = [f](auto e) { return e % f == 0; };
  auto must_have = [m](auto e) {
    return std::to_string(e).find(std::to_string(m)) != std::string::npos;
  };
  auto predicate = [=](auto e) {
    return factor(e) ? must_have(e) : false;
  };
  
  // return (std::views::iota(1, n + 1) | std::views::filter(predicate));
  return std::ranges::distance(std::views::iota(1, n + 1) | std::views::filter(predicate));
}

int main() {
  // for(auto&& it : find_winners(3,5,100)) std::cout<<it<<'\n'; // prints 15 45 51 54 57 75
  std::cout<<find_winners(3,5,100); // prints 6
}
