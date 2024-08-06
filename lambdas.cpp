#include <iostream>
#include <string>
#include <utility>

// The commented out section is valid for lambda composition, but only for single param lambda functions
// template <typename F>
// auto compose(F&& f) {
//   return [=](auto x) {
//     return f(x); }; }

// template <typename F, typename G>
// auto compose(F&& f, G&& g) {
//   return [=](auto x) {
//     return f(g(x)); }; }

// template <typename F, typename... R>
// auto compose(F&& f, R&&... r) {
//   return [=](auto x) {
//     return f(compose(r...)(x)); }; }

// auto n = compose(
//   [] (int const n) {return std::to_string(n); },
//   [] (int const n) {return n * n; },
//   [] (int const n) {return n + n; },
//   [] (int const n) {return std::abs(n); }); 

// auto v = compose(
//   [](int const n) {return std::to_string(n); },
//   [](int const n) {return n * n; })(-3);// n = "9"

template <typename F, typename... G>
consteval auto compose(F&& f, G&&... g) {
  return [=](auto&&... args) {
    return f(compose(g...)(std::forward<decltype(args)>(args)...));
  };
}

template <typename F>
consteval auto compose(F&& f) {
  return [=](auto&&... args) {
    return f(std::forward<decltype(args)>(args)...);
  };
}

constexpr auto add = [](int x, int y) { return x + y; };
constexpr auto multiply = [](int x) { return x * 2; };
constexpr auto composed = compose(multiply, add);

int main() {
  std::cout << composed(3, 4) << std::endl; // (3 + 4) * 2 = 14
  return 0;
}
