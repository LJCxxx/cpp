#include <concepts>
#include <cstdlib>
#include <iostream>

template<class T>
concept Numerical = std::is_integral_v<T> || std::is_floating_point_v<T>;

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
void gemm_T(const T* A, const T* BT, T* C, size_t rowA, size_t colA, size_t colB) {
  for(int i = 0; i < rowA; i++) {
    for(int j = 0; j < colB; j++) {
      for(size_t k = 0; k < colA; k++) {
        C[i * colB + j] += A[i * colA + k] * BT[j * colB + k];
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

int main() {

  const unsigned int rowA = 5, colA = 5, colB = 5;

  const float A[] {
    3.4, 5.7, 6.3, 7.4, 2.9,
    7.8, 1.3, 3.1, 5.2, 4.0,
    6.2, 8.6, 9.9, 8.8, 7.5,
    4.5, 2.7, 4.8, 3.7, 1.6,
    9.1, 7.2, 1.5, 6.6, 9.4
  };

  const float B[] {
    8.5, 3.9, 6.7, 7.6, 1.7,
    4.2, 7.1, 9.8, 3.5, 5.4,
    2.7, 5.6, 1.4, 6.1, 4.3,
    9.3, 2.4, 4.9, 2.3, 7.0,
    1.8, 8.0, 3.2, 8.9, 9.7
  };

  float BT[25] {0.0f};

  transpose(B,BT, 5, 5);

  float C[rowA * colB] {0.0f};

  gemm_T(A, BT, C, rowA, colA, colB);

  for(int i = 0; i < 25;  i++) {
    std::cout<< C[i] << ((i+1)%colB == 0 ? "\n" : ", ");
  }
  // prints:
  // 143.89, 129.97, 133, 127.05, 143.58
  // 135.69, 101.49, 107.62, 130.3, 108.81
  // 210.89, 221.8, 206.8, 224.6, 233.9
  // 99.84, 85.28, 86.58, 95.68, 84.29
  // 189.94, 186.05, 196.05, 202.35, 198.18
}