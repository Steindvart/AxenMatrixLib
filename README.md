# AxenMatrixLib — A library for working with matrices in C++

AxenMatrixLib is a compact and test-covered library for working with matrices in C++. It implements core linear algebra operations, including arithmetic, determinant calculation, transposition, inverse matrix, and other matrix operations. The project is developed as a pet project with a focus on clean code, test coverage, and ease of integration.

## Features

- **Matrix creation and copying**
- **Arithmetic operations**: addition, subtraction, multiplication by scalars and matrices.
- **Flexible size handling**: ability to dynamically change the number of rows and columns.
- **Matrix comparison**: accounting for computational precision errors.
- **Determinant calculation**: using the Laplace algorithm.
- **Inverse matrix**
- **Transposition**
- **Calculation of the matrix of cofactors (complements)**
- **Boundary case checking and exception throwing on errors**
- **Full unit test coverage**
- **Integration and build by CMake**

## Ideas for Project Development
1. Make the matrix class templated to support types that behave like numbers.
2. Implement a more efficient determinant calculation algorithm, such as Gaussian elimination.
3. Add support for atomic operations for thread safety.
4. Implement iterators for the matrix class.
5. Create adapters for integration with STL containers.

## Quick Start

### Requirements

- C++20 compatible compiler (GCC, Clang, MSVC)
- [CMake](https://cmake.org/) 3.21+
- [GoogleTest](https://github.com/google/googletest) (automatically detected via find_package)

### Build

```bash
git clone https://github.com/Steindvart/AxenMatrixLib.git
cd AxenMatrixLib
mkdir build && cd build
cmake ..
make
```

### Running Tests

```bash
ctest --output-on-failure
# or directly
./src/MatrixLibTests/MatrixLibTests
```

### Usage
Add MatrixLib as a submodule or include it via CMake.

```cmake
add_subdirectory(MatrixLib)
target_link_libraries(YourTarget PRIVATE MatrixLib)
```

### Example Usage
```cpp
#include <axen/MatrixLib/Matrix.h>

int main() {
    Matrix a(3, 3);
    Matrix b(3, 3);
    // ... fill a and b ...
    Matrix c = a + b;
    Matrix d = a * b;
    double determinantA = a.Determinant();
    Matrix inverseA = a.Inverse();
}
```
