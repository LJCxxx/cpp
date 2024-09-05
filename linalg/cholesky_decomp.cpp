#include <concepts>
#include <cstdlib>
#include <cmath>
#include <iostream>

template<class T>
concept Numerical = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <Numerical T>
void cholesky_decompositon(const T* A, T* L, const size_t size) {
  T tmp = 0;
  for(int i = 0; i < size; i++) {
    for(int j = 0; j <= i; j++) {
      tmp = A[size * i + j];
      if(i == j) {
        for(int k = 0; k < j; k++) {
          tmp -= L[size * i + k] * L[size * i + k];
        }
        L[size * i + j] = std::sqrt(tmp);
      } else {
        for(int k = 0; k < j; k++) {
          tmp -= L[size * i + k] * L[size * j + k];
        }
        L[size * i + j] = tmp / L[size * j + j];
      }
    }
  }
}

template <Numerical T>
void gemm(const T* A, const T* B, T* C, size_t rowA, size_t colA, size_t colB) {
  for(size_t i = 0; i < rowA; i++) {
    for(size_t j = 0; j < colB; j++) {
      for(size_t k = 0; k < colA; k++) {
        C[i * colB + j] += A[i * colA + k] * B[k * colB + j];
      }
    }
  }
};

template <Numerical T>
void transpose(const T* A, T* AT, size_t rowA, size_t colA) {
  for(size_t i = 0; i < colA; i++) {
    for(size_t j = 0; j < rowA; j++) {
      AT[i * rowA + j] = A[j * colA + i];
    }
  }
};

void print(auto* A, size_t rowA, size_t colA) {
  for(int i = 0; i < rowA * colA;  i++) {
    std::cout<< A[i] << ((i+1)%rowA == 0 ? "\n" : ", ");
  }
} 

int main() {
  unsigned const int sizeA = 3;
  float A[sizeA * sizeA] {
    4, 12, -16,
    12, 37, -43,
    -16, -43, 98
  };

  float L[sizeA * sizeA] {0.0};
  float LT[sizeA * sizeA] {0.0};
  float LLT[sizeA * sizeA] {0.0};

  cholesky_decompositon(A, L, sizeA);
  transpose(L, LT, sizeA, sizeA);
  gemm(L, LT, LLT, sizeA, sizeA, sizeA);
  
  std::cout<< "matrix A:\n";
  print(A, sizeA, sizeA);

  std::cout<< "\nmatrix L:\n";
  print(L, sizeA, sizeA);

  std::cout<< "\nmatrix LT:\n";
  print(LT, sizeA, sizeA);

  std::cout<< "\nmatrix LLT:\n";
  print(LLT, sizeA, sizeA);
}
// prints
// 
// matrix A:
// 4, 12, -16
// 12, 37, -43
// -16, -43, 98

// matrix L:
// 2, 0, 0
// 6, 1, 0
// -8, 5, 3

// matrix LT:
// 2, 6, -8
// 0, 1, 5
// 0, 0, 3

// matrix LLT:
// 4, 12, -16
// 12, 37, -43
// -16, -43, 98