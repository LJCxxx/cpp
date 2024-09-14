# linalg

**gemm.cpp** implements a general matrix multiplication (GEMM) function for computing the dot product of matrices A and B. The gemm_T function variant handles cases where matrix B is transposed before multiplication. Additionally, a transpose function is included.\
<br/>
**cholesky_decomp.cpp** implements Cholesky Decomposition, a method for decomposing a positive definite matrix in a product of a lower triangular matrix and its transpose A = LLT, where A is a symmetric, positive definite matrix, L is a lower triangular matrix, and LT is L transposed. It is faster and more efficient for certain matrix types than general-purpose decompositions, and numerically stable.\
<br/>
**eigen_value.cpp** calculates eigenvalues for a 2×2 matrix, serving as a basic introduction to the concept. Eigenvalues and eigenvectors are crucial in various fields, including machine learning for Principal Component Analysis, quantum mechanics for solving wave functions, and system stability analysis. The plan is to extend this to 𝑛×𝑛 matrices and add eigenvector calculations, addressing more complex numerical methods and applications.\
<br/>
Although these functions are designed for 2D matrices, the values are stored in a flat 1D array, following conventions similar to those used in BLAS/LAPACK. C++20 concepts is used to constrain the template arguments, which felt like an appropriate use case—similar to C++11 static_asserts. While actual linear algebra implementations could benefit from further optimizations and parallelism/concurrency, the O3 optimization level automatically leverages SIMD registers, providing more than sufficient performance for typical use cases.
