#include <concepts>
#include <array>
#include <cmath>
#include <iostream>

// eigen for 2x2 matrices
template<class T>
concept Numerical = std::is_integral_v<T> || std::is_floating_point_v<T>;

template<Numerical T>auto eigen_values(T A[4]) -> std::array<T, 2>;
template<Numerical T>auto quadratic(T a, T b, T c) -> std::array<T, 2>;

int main() {
  float A[4] {1, 2, 3, -4};
  auto e_val = eigen_values(A);
  std::cout<< "eigen values: " << e_val[0] << ", " << e_val[1]; // 2,-5
}

template<Numerical T>
auto eigen_values(T A[4]) -> std::array<T, 2> {
  return quadratic(static_cast<T>(1), - A[0] - A[3], (A[0] * A[3]) - (A[1] * A[2]));
}

template<Numerical T>
auto quadratic(T a, T b, T c) -> std::array<T, 2> {
  return std::array<T, 2> {
    static_cast<T>((-b + std::sqrt(b * b - static_cast<T>(4) * a * c)) / (static_cast<T>(2) * a)),
    static_cast<T>((-b - std::sqrt(b * b - static_cast<T>(4) * a * c)) / (static_cast<T>(2) * a)),
  };
}