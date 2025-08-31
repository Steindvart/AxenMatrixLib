#pragma once

#include <cstddef>
#include <vector>

namespace axen
{

class Matrix
{
 public:
  static constexpr double EPS = 1e-7;

  Matrix();
  Matrix(size_t rows, size_t cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other) noexcept;
  ~Matrix() = default;

  size_t GetRows() const noexcept { return m_rows; };
  size_t GetCols() const noexcept { return m_cols; };

  void SetRows(size_t value);
  void SetCols(size_t value);

  double At(size_t row, size_t col) const;
  double& At(size_t row, size_t col);

  double GetValue(size_t row, size_t col) const;
  double& GetValue(size_t row, size_t col);

  // Logic
  bool Equal(const Matrix& other) const noexcept;

  // Arithmetic
  void Sum(const Matrix& other);
  void Sub(const Matrix& other);
  void Mult(double num) noexcept;
  void Mult(const Matrix& other);

  // Other
  Matrix Transpose() const;
  Matrix CalcComplements() const;
  double Determinant() const;
  Matrix Inverse() const;

  // Operators
  double& operator()(size_t row, size_t col);
  double operator()(size_t row, size_t col) const;
  bool operator==(const Matrix& other) const noexcept;

  Matrix& operator=(Matrix&& other) noexcept;
  Matrix& operator=(const Matrix& other);

  Matrix operator+(const Matrix& other) const;
  Matrix operator+=(const Matrix& other);

  Matrix operator-(const Matrix& other) const;
  Matrix operator-=(const Matrix& other);

  Matrix operator*(double num) const;
  Matrix operator*(const Matrix& other) const;
  Matrix operator*=(double num);
  Matrix operator*=(const Matrix& other);
  friend Matrix operator*(const double& value, const Matrix& matrix);

  // Utils
  static void CopyVals(const Matrix& src, Matrix& dest);
  static void CopyValsWithSkip(const Matrix& src, Matrix& dest, size_t rowForSkip, size_t colForSkip);
  static void Swap(Matrix& one, Matrix& second);

 private:
  size_t m_rows;
  size_t m_cols;
  std::vector<double> m_data;

  enum class Operation
  {
    Sum,
    Substract
  };

  void CalcMatrix(const Matrix& matrix, Operation operation) noexcept;
  double CalcDeterminantLaplacian() const;
};

} // namespace axen
