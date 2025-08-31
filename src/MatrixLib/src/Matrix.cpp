#include "Matrix.h"

#include <cmath>
#include <stdexcept>
#include <utility>

#include "Utils.h"

namespace axen
{

/* Construction, Distruction */

Matrix::Matrix() : Matrix(1, 1)
{
}

Matrix::Matrix(size_t rows, size_t cols) : m_rows {rows}, m_cols {cols}, m_data(rows * cols, 0.0)
{
  if ((m_rows <= 0) || (m_cols <= 0))
  {
    throw std::invalid_argument("Size of matrix cannot be zero or negative");
  }
}

Matrix::Matrix(const Matrix& other) : Matrix(other.m_rows, other.m_cols)
{
  CopyVals(other, *this);
}

Matrix::Matrix(Matrix&& other) noexcept : m_rows {other.m_rows}, m_cols {other.m_cols}
{
  other.m_rows = 0;
  other.m_cols = 0;
  std::swap(m_data, other.m_data);
}

/* Getters, Setters */

void Matrix::SetRows(size_t value)
{
  if (m_rows == value)
  {
    return;
  }

  if (value <= 0)
  {
    throw std::invalid_argument("Size of rows of matrix cannot be zero or negative");
  }

  Matrix tmp = Matrix(value, m_cols);
  CopyVals(*this, tmp);
  Swap(*this, tmp);
}

void Matrix::SetCols(size_t value)
{
  if (m_cols == value)
  {
    return;
  }

  if (value <= 0)
  {
    throw std::invalid_argument("Size of columns of matrix cannot be zero or negative");
  }

  Matrix tmp = Matrix(m_rows, value);
  CopyVals(*this, tmp);
  Swap(*this, tmp);
}

inline double Matrix::At(size_t row, size_t col) const
{
  if ((row >= m_rows) || (col >= m_cols))
  {
    throw std::out_of_range("Index out of range");
  }

  return GetValue(row, col);
}

inline double& Matrix::At(size_t row, size_t col)
{
  if ((row >= m_rows) || (col >= m_cols))
  {
    throw std::out_of_range("Index out of range");
  }

  return GetValue(row, col);
}

inline double Matrix::GetValue(size_t row, size_t col) const
{
  return m_data[row * m_cols + col];
}

inline double& Matrix::GetValue(size_t row, size_t col)
{
  return m_data[row * m_cols + col];
}

/* Logic */

bool Matrix::Equal(const Matrix& other) const noexcept
{
  if ((m_rows != other.m_rows) || (m_cols != other.m_cols))
  {
    return false;
  }

  for (size_t row = 0; row < m_rows; row++)
  {
    for (size_t col = 0; col < m_cols; col++)
    {
      if (!utils::IsDoublesEq(GetValue(row, col), other(row, col), EPS))
      {
        return false;
      }
    }
  }

  return true;
}

/* Arithmetic */

void Matrix::CalcMatrix(const Matrix& other, Operation operation) noexcept
{
  for (size_t row = 0; row < m_rows; row++)
  {
    for (size_t col = 0; col < m_cols; col++)
    {
      if (operation == Operation::Sum)
      {
        GetValue(row, col) += other(row, col);
      }
      else if (operation == Operation::Substract)
      {
        GetValue(row, col) -= other(row, col);
      }
    }
  }
}

void Matrix::Sum(const Matrix& other)
{
  if ((m_rows != other.m_rows) || (m_cols != other.m_cols))
  {
    throw std::domain_error("Order inconsistencies of matrices in sum operation");
  }

  CalcMatrix(other, Operation::Sum);
}

void Matrix::Sub(const Matrix& other)
{
  if ((m_rows != other.m_rows) || (m_cols != other.m_cols))
  {
    throw std::domain_error("Order inconsistencies of matrices in sub operation");
  }

  CalcMatrix(other, Operation::Substract);
}

void Matrix::Mult(double num) noexcept
{
  for (size_t row = 0; row < m_rows; row++)
  {
    for (size_t col = 0; col < m_cols; col++)
    {
      GetValue(row, col) *= num;
    }
  }
}

void Matrix::Mult(const Matrix& other)
{
  if (m_cols != other.m_rows)
  {
    throw std::domain_error("Order inconsistencies of matrices in mult operation: (a.cols != b.rows)");
  }

  Matrix tmp = Matrix(m_rows, other.m_cols);
  for (size_t row = 0; row < m_rows; row++)
  {
    for (size_t col = 0; col < other.m_cols; col++)
    {
      for (size_t k = 0; k < other.m_rows; k++)
      {
        tmp(row, col) += GetValue(row, k) * other(k, col);
      }
    }
  }

  Swap(*this, tmp);
}

/* Other */

Matrix Matrix::Transpose() const
{
  Matrix result = Matrix(m_cols, m_rows);

  for (size_t col = 0; col < m_cols; col++)
  {
    for (size_t row = 0; row < m_rows; row++)
    {
      result(col, row) = GetValue(row, col);
    }
  }

  return result;
}

Matrix Matrix::CalcComplements() const
{
  if (m_rows != m_cols)
  {
    throw std::domain_error("The matrix is not square");
  }

  Matrix result = Matrix(m_cols, m_rows);

  if (m_rows == 1)
  {
    result(0, 0) = 1;
    return result;
  }

  for (size_t row = 0; row < m_rows; row++)
  {
    for (size_t col = 0; col < m_cols; col++)
    {
      Matrix minor = Matrix(m_rows - 1, m_cols - 1);

      CopyValsWithSkip(*this, minor, row, col);

      int sign = utils::IsEven(row + col) ? 1 : -1;
      result(row, col) = sign * minor.CalcDeterminantLaplacian();
    }
  }

  return result;
}

double Matrix::Determinant() const
{
  if (m_rows != m_cols)
  {
    throw std::domain_error("The matrix is not square");
  }

  return CalcDeterminantLaplacian();
}

// #DEFECT - Poor accuracy when working with large fractions
double Matrix::CalcDeterminantLaplacian() const
{
  if (GetRows() == 1)
  {
    return GetValue(0, 0);
  }

  if (GetRows() == 2 && GetCols() == 2)
  {
    return GetValue(0, 0) * GetValue(1, 1) - GetValue(0, 1) * GetValue(1, 0);
  }

  double result = 0.;
  Matrix minor = Matrix(GetRows() - 1, GetCols() - 1);

  int sign = 1;
  for (size_t col = 0; col < GetCols(); col++)
  {
    CopyValsWithSkip(*this, minor, 0, col);

    result += sign * (GetValue(0, col) * minor.CalcDeterminantLaplacian());
    sign = -sign;
  }

  return result;
}

Matrix Matrix::Inverse() const
{
  double determinant = Determinant();
  if (fabs(determinant) < EPS)
  {
    throw std::domain_error("Determinant of the matrix is 0");
  }

  Matrix transposed = CalcComplements().Transpose();
  Matrix result = Matrix(m_cols, m_rows);

  for (size_t col = 0; col < m_rows; col++)
  {
    for (size_t row = 0; row < m_cols; row++)
    {
      result(col, row) = transposed(col, row) / determinant;
    }
  }

  return result;
}

/* Operators */

double& Matrix::operator()(size_t row, size_t col)
{
  return At(row, col);
}

double Matrix::operator()(size_t row, size_t col) const
{
  return At(row, col);
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
  if (this == &other)
  {
    return *this;
  }

  m_rows = other.m_rows;
  m_cols = other.m_cols;
  std::swap(m_data, other.m_data);

  other.m_rows = 0;
  other.m_cols = 0;

  return *this;
}

Matrix& Matrix::operator=(const Matrix& other)
{
  if (this == &other)
  {
    return *this;
  }

  Matrix tmp = Matrix(other.m_rows, other.m_cols);
  CopyVals(other, tmp);
  Swap(*this, tmp);

  return *this;
}

bool Matrix::operator==(const Matrix& other) const noexcept
{
  return Equal(other);
}

Matrix Matrix::operator+(const Matrix& other) const
{
  Matrix result(*this);
  result.Sum(other);

  return result;
}

Matrix Matrix::operator+=(const Matrix& other)
{
  Sum(other);
  return *this;
}

Matrix Matrix::operator-(const Matrix& other) const
{
  Matrix result(*this);
  result.Sub(other);

  return result;
}

Matrix Matrix::operator-=(const Matrix& other)
{
  Sub(other);
  return *this;
}

Matrix Matrix::operator*(const double num) const
{
  Matrix result(*this);
  result.Mult(num);

  return result;
}

Matrix Matrix::operator*=(const double num)
{
  Mult(num);
  return *this;
}

Matrix Matrix::operator*(const Matrix& other) const
{
  Matrix result(*this);
  result.Mult(other);

  return result;
}

Matrix Matrix::operator*=(const Matrix& other)
{
  Mult(other);
  return *this;
}

/* friend */ Matrix operator*(const double& value, const Matrix& matrix)
{
  return matrix * value;
}

/* Utils */

void Matrix::CopyVals(const Matrix& src, Matrix& dest)
{
  size_t rows = std::min(dest.m_rows, src.m_rows);
  size_t cols = std::min(dest.m_cols, src.m_cols);

  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      dest(i, j) = src(i, j);
    }
  }
}

void Matrix::CopyValsWithSkip(const Matrix& src, Matrix& dest, size_t rowForSkip, size_t colForSkip)
{
  size_t to_i = 0;
  for (size_t i = 0; i < src.GetRows(); i++)
  {
    if (i == rowForSkip)
    {
      continue;
    }

    size_t to_j = 0;
    for (size_t j = 0; j < src.GetCols(); j++)
    {
      if (j == colForSkip)
      {
        continue;
      }

      dest(to_i, to_j) = src(i, j);
      to_j++;
    }

    to_i++;
  }
}

void Matrix::Swap(Matrix& one, Matrix& second)
{
  std::swap(one.m_rows, second.m_rows);
  std::swap(one.m_cols, second.m_cols);
  std::swap(one.m_data, second.m_data);
}

}  // namespace axen
