#include "TestsSuite.h"

using namespace tests;

/* NORMAL */

class MatrixArithmeticTestsNormal : public testing::Test
{
  void SetUp() override
  {
    srand(static_cast<unsigned int>(time(0)) + getpid());
  }
};

TEST_F(MatrixArithmeticTestsNormal, sum_matrix_is_correct)
{
  const size_t rows = rand() % MaxRows + 1;
  const size_t cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = Matrix(rows, cols);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      check(i, j) = a(i, j) + b(i, j);
    }
  }

  a.Sum(b);
  EXPECT_TRUE(a.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, sum_operator_matrix_is_correct)
{
  const size_t rows = rand() % MaxRows + 1;
  const size_t cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = Matrix(rows, cols);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      check(i, j) = a(i, j) + b(i, j);
    }
  }

  Matrix res = a + b;
  EXPECT_TRUE(res.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, sum_eq_operator_matrix_is_correct)
{
  const size_t rows = rand() % MaxRows + 1;
  const size_t cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = Matrix(rows, cols);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      check(i, j) = a(i, j) + b(i, j);
    }
  }

  a += b;
  EXPECT_TRUE(a.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, sub_matrix_is_correct)
{
  const size_t rows = rand() % MaxRows + 1;
  const size_t cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = Matrix(rows, cols);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      check(i, j) = a(i, j) - b(i, j);
    }
  }

  a.Sub(b);
  EXPECT_TRUE(a.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, sub_operator_matrix_is_correct)
{
  const size_t rows = rand() % MaxRows + 1;
  const size_t cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = Matrix(rows, cols);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      check(i, j) = a(i, j) - b(i, j);
    }
  }

  Matrix res = a - b;
  EXPECT_TRUE(res.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, sub_eq_operator_matrix_is_correct)
{
  const size_t rows = rand() % MaxRows + 1;
  const size_t cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = Matrix(rows, cols);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      check(i, j) = a(i, j) - b(i, j);
    }
  }

  a -= b;
  EXPECT_TRUE(a.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, mult_matrix_by_matrix_is_correct)
{
  const size_t rows = rand() % MaxRows + 1;
  const size_t cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = Matrix(cols, rows);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  Matrix check = Matrix(a.GetRows(), b.GetCols());
  for (int i = 0; i < a.GetRows(); i++)
  {
    for (int j = 0; j < b.GetCols(); j++)
    {
      for (int k = 0; k < b.GetRows(); k++)
      {
        check(i, j) += a(i, k) * b(k, j);
      }
    }
  }

  a.Mult(b);
  EXPECT_TRUE(a.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, mult_matrix_by_number_is_correct)
{
  const size_t rows = rand() % MaxRows + 1;
  const size_t cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  double num = utils::GetRandom(FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      check(i, j) = a(i, j) * num;
    }
  }

  a.Mult(num);
  EXPECT_TRUE(a.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, by_operator_mult_matrix_by_number_is_correct)
{
  const int rows = rand() % MaxRows + 1;
  const int cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  double num = utils::GetRandom(FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      check(i, j) = a(i, j) * num;
    }
  }

  Matrix res = a * num;
  EXPECT_TRUE(res.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, by_operator_mult_matrix_by_matrix_is_correct)
{
  const int rows = rand() % MaxRows + 1;
  const int cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = Matrix(cols, rows);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  Matrix check = Matrix(a.GetRows(), b.GetCols());
  for (int i = 0; i < a.GetRows(); i++)
  {
    for (int j = 0; j < b.GetCols(); j++)
    {
      for (int k = 0; k < b.GetRows(); k++)
      {
        check(i, j) += a(i, k) * b(k, j);
      }
    }
  }

  Matrix res = a * b;
  EXPECT_TRUE(res.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, by_operator_mult_number_by_matrix_is_correct)
{
  const int rows = rand() % MaxRows + 1;
  const int cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  double num = utils::GetRandom(FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      check(i, j) = a(i, j) * num;
    }
  }

  Matrix res = num * a;
  EXPECT_TRUE(res.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, by_operator_mult_eq_matrix_by_number_is_correct)
{
  const int rows = rand() % MaxRows + 1;
  const int cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  double num = utils::GetRandom(FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      check(i, j) = a(i, j) * num;
    }
  }

  a *= num;
  EXPECT_TRUE(a.Equal(check));
}

TEST_F(MatrixArithmeticTestsNormal, mult_eq_matrix_by_matrix_operator_is_correct)
{
  const int rows = rand() % MaxRows + 1;
  const int cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = Matrix(cols, rows);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  Matrix check = Matrix(a.GetRows(), b.GetCols());
  for (int i = 0; i < a.GetRows(); i++)
  {
    for (int j = 0; j < b.GetCols(); j++)
    {
      for (int k = 0; k < b.GetRows(); k++)
      {
        check(i, j) += a(i, k) * b(k, j);
      }
    }
  }

  a *= b;
  EXPECT_TRUE(a.Equal(check));
}

/* EDGE */

class MatrixArithmeticTestsEdge : public testing::Test
{
};

TEST_F(MatrixArithmeticTestsEdge, mult_matrix_same_cols_rows_is_correct)
{
  const size_t rows_a = 20;
  const size_t cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  const size_t rows_b = 10;
  const size_t cols_b = 30;
  Matrix b = Matrix(rows_b, cols_b);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  Matrix check = Matrix(a.GetRows(), b.GetCols());
  for (int i = 0; i < a.GetRows(); i++)
  {
    for (int j = 0; j < b.GetCols(); j++)
    {
      for (int k = 0; k < b.GetRows(); k++)
      {
        check(i, j) += a(i, k) * b(k, j);
      }
    }
  }

  a.Mult(b);
  EXPECT_TRUE(a.Equal(check));
}

TEST_F(MatrixArithmeticTestsEdge, mult_matrix_by_number_same_cols_rows_is_correct)
{
  const int rows_a = 20;
  const int cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  double num = utils::GetRandom(FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows_a, cols_a);
  for (int i = 0; i < rows_a; i++)
  {
    for (int j = 0; j < cols_a; j++)
    {
      check(i, j) = a(i, j) * num;
    }
  }

  Matrix res = a * num;
  EXPECT_TRUE(res.Equal(check));
}

TEST_F(MatrixArithmeticTestsEdge, by_operator_mult_number_by_matrix_same_cols_rows_is_correct)
{
  const int rows_a = 20;
  const int cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  double num = utils::GetRandom(FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows_a, cols_a);
  for (int i = 0; i < rows_a; i++)
  {
    for (int j = 0; j < cols_a; j++)
    {
      check(i, j) = a(i, j) * num;
    }
  }

  Matrix res = num * a;
  EXPECT_TRUE(res.Equal(check));
}

TEST_F(MatrixArithmeticTestsEdge, by_operator_mult_eq_matrix_by_number_same_cols_rows_is_correct)
{
  const int rows_a = 20;
  const int cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  double num = utils::GetRandom(FLT_MIN, FLT_MAX);

  Matrix check = Matrix(rows_a, cols_a);
  for (int i = 0; i < rows_a; i++)
  {
    for (int j = 0; j < cols_a; j++)
    {
      check(i, j) = a(i, j) * num;
    }
  }

  a *= num;
  EXPECT_TRUE(a.Equal(check));
}

/* ANOMALY */

class MatrixArithmeticTestsAnomaly : public testing::Test
{
};

TEST_F(MatrixArithmeticTestsAnomaly, sum_matrix_different_size_throws)
{
  const size_t rows_a = 20;
  const size_t cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);

  const size_t rows_b = 30;
  const size_t cols_b = 30;
  Matrix b = Matrix(rows_b, cols_b);

  EXPECT_THROW({ a.Sum(b); }, std::domain_error);
}

TEST_F(MatrixArithmeticTestsAnomaly, sum_operator_different_size_throws)
{
  const size_t rows_a = 20;
  const size_t cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);

  const size_t rows_b = 30;
  const size_t cols_b = 30;
  Matrix b = Matrix(rows_b, cols_b);

  EXPECT_THROW({ a + b; }, std::domain_error);
}

TEST_F(MatrixArithmeticTestsAnomaly, sum_eq_operator_different_size_throws)
{
  const size_t rows_a = 20;
  const size_t cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);

  const size_t rows_b = 30;
  const size_t cols_b = 30;
  Matrix b = Matrix(rows_b, cols_b);

  EXPECT_THROW({ a += b; }, std::domain_error);
}

TEST_F(MatrixArithmeticTestsAnomaly, sub_matrix_different_size_throws)
{
  const size_t rows_a = 20;
  const size_t cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);

  const size_t rows_b = 30;
  const size_t cols_b = 30;
  Matrix b = Matrix(rows_b, cols_b);

  EXPECT_THROW({ a.Sub(b); }, std::domain_error);
}

TEST_F(MatrixArithmeticTestsAnomaly, sub_operator_different_size_throws)
{
  const size_t rows_a = 20;
  const size_t cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);

  const size_t rows_b = 30;
  const size_t cols_b = 30;
  Matrix b = Matrix(rows_b, cols_b);

  EXPECT_THROW({ a - b; }, std::domain_error);
}

TEST_F(MatrixArithmeticTestsAnomaly, sub_eq_operator_different_size_throws)
{
  const size_t rows_a = 20;
  const size_t cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);

  const size_t rows_b = 30;
  const size_t cols_b = 30;
  Matrix b = Matrix(rows_b, cols_b);

  EXPECT_THROW({ a -= b; }, std::domain_error);
}

TEST_F(MatrixArithmeticTestsEdge, mult_matrix_different_cols_rows_throws)
{
  const size_t rows_a = 20;
  const size_t cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);

  const size_t rows_b = 30;
  const size_t cols_b = 30;
  Matrix b = Matrix(rows_b, cols_b);

  EXPECT_THROW({ a.Mult(b); }, std::domain_error);
}
