#include "TestsSuite.h"

using namespace tests;
using namespace axen;

/* NORMAL */

class MatrixMathTestsNormal : public testing::Test
{
};

TEST_F(MatrixMathTestsNormal, calc_complements_3x3_is_correct)
{
  const size_t rows = 3;
  const size_t cols = 3;

  Matrix expected = Matrix(rows, cols);
  expected(0, 0) = 0;
  expected(0, 1) = 10;
  expected(0, 2) = -20;
  expected(1, 0) = 4;
  expected(1, 1) = -14;
  expected(1, 2) = 8;
  expected(2, 0) = -8;
  expected(2, 1) = -2;
  expected(2, 2) = 4;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 0;
  a(1, 1) = 4;
  a(1, 2) = 2;
  a(2, 0) = 5;
  a(2, 1) = 2;
  a(2, 2) = 1;

  Matrix actual = a.CalcComplements();
  EXPECT_TRUE(actual.Equal(expected));
}

TEST_F(MatrixMathTestsNormal, determinant_1x1_is_correct)
{
  const size_t rows = 1;
  const size_t cols = 1;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1.00006;

  double expected = 1.00006;
  double actual = a.Determinant();
  EXPECT_NEAR(actual, expected, TestsEPS);
}

TEST_F(MatrixMathTestsNormal, determinant_2x2_is_correct)
{
  const size_t rows = 2;
  const size_t cols = 2;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1.00006;
  a(0, 1) = 53;
  a(1, 0) = 6.4;
  a(1, 1) = 1;

  double expected = -338.19994;
  double actual = a.Determinant();
  EXPECT_NEAR(actual, expected, TestsEPS);
}

TEST_F(MatrixMathTestsNormal, determinant_3x3_whole_is_correct)
{
  const size_t rows = 3;
  const size_t cols = 3;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1;
  a(0, 1) = 53;
  a(0, 2) = 89;
  a(1, 0) = 6;
  a(1, 1) = 1;
  a(1, 2) = 43;
  a(2, 0) = 62;
  a(2, 1) = 34;
  a(2, 2) = 4;

  double expected = 151206;
  double actual = a.Determinant();
  EXPECT_NEAR(actual, expected, TestsEPS);
}

TEST_F(MatrixMathTestsNormal, determinant_3x3_float_is_correct)
{
  const size_t rows = 3;
  const size_t cols = 3;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1.6;
  a(0, 1) = 53;
  a(0, 2) = 89.3;
  a(1, 0) = 6.4;
  a(1, 1) = 1;
  a(1, 2) = 0.4;
  a(2, 0) = 62.4;
  a(2, 1) = 34.5;
  a(2, 2) = 0.4;

  double expected = 15310.88;
  double actual = a.Determinant();
  EXPECT_NEAR(actual, expected, TestsEPS);
}

TEST_F(MatrixMathTestsNormal, determinant_5x5_whole_is_correct)
{
  const size_t rows = 5;
  const size_t cols = 5;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 0;
  a(0, 1) = 6;
  a(0, 2) = -2;
  a(0, 3) = -1;
  a(0, 4) = 5;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(1, 3) = -9;
  a(1, 4) = -7;
  a(2, 0) = 0;
  a(2, 1) = 15;
  a(2, 2) = 35;
  a(2, 3) = -9;
  a(2, 4) = -7;
  a(3, 0) = 0;
  a(3, 1) = -1;
  a(3, 2) = -11;
  a(3, 3) = -2;
  a(3, 4) = 1;
  a(4, 0) = -2;
  a(4, 1) = -2;
  a(4, 2) = 3;
  a(4, 3) = 0;
  a(4, 4) = -2;

  double expected = 2480;
  double actual = a.Determinant();
  EXPECT_NEAR(actual, expected, TestsEPS);
}

TEST_F(MatrixMathTestsNormal, inverse_3x3_is_correct_0)
{
  const size_t rows = 3;
  const size_t cols = 3;

  Matrix expected = Matrix(rows, cols);
  expected(0, 0) = 44300.0 / 367429.0;
  expected(0, 1) = -236300.0 / 367429.0;
  expected(0, 2) = 200360.0 / 367429.0;
  expected(1, 0) = 20600.0 / 367429.0;
  expected(1, 1) = 56000.0 / 367429.0;
  expected(1, 2) = -156483.0 / 367429.0;
  expected(2, 0) = 30900.0 / 367429.0;
  expected(2, 1) = 84000.0 / 367429.0;
  expected(2, 2) = -51010.0 / 367429.0;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 2.8;
  a(0, 1) = 1.3;
  a(0, 2) = 7.01;
  a(1, 0) = -1.03;
  a(1, 1) = -2.3;
  a(1, 2) = 3.01;
  a(2, 0) = 0;
  a(2, 1) = -3;
  a(2, 2) = 2;

  Matrix actual = a.Inverse();
  EXPECT_TRUE(actual.Equal(expected));
}

TEST_F(MatrixMathTestsNormal, inverse_3x3_is_correct_1)
{
  const size_t rows = 3;
  const size_t cols = 3;

  Matrix expected = Matrix(rows, cols);
  expected(0, 0) = 1.0;
  expected(0, 1) = -1.0;
  expected(0, 2) = 1.0;
  expected(1, 0) = -38.0;
  expected(1, 1) = 41.0;
  expected(1, 2) = -34.0;
  expected(2, 0) = 27.0;
  expected(2, 1) = -29.0;
  expected(2, 2) = 24.0;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 2.0;
  a(0, 1) = 5.0;
  a(0, 2) = 7.0;
  a(1, 0) = 6.0;
  a(1, 1) = 3.0;
  a(1, 2) = 4.0;
  a(2, 0) = 5.0;
  a(2, 1) = -2.0;
  a(2, 2) = -3.0;

  Matrix actual = a.Inverse();
  EXPECT_TRUE(actual.Equal(expected));
}

TEST_F(MatrixMathTestsNormal, transpose_matrix_is_correct)
{
  srand(time(0) + getpid());

  const size_t rows = rand() % MaxRows + 1;
  const size_t cols = rand() % MaxCols + 1;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix check = Matrix(cols, rows);
  for (int i = 0; i < a.GetCols(); i++)
  {
    for (int j = 0; j < a.GetRows(); j++)
    {
      check(i, j) = a(j, i);
    }
  }

  Matrix res = a.Transpose();
  EXPECT_TRUE(check.Equal(res));
}

/* EDGE */

class MatrixMathTestsEdge : public testing::Test
{
};

TEST_F(MatrixMathTestsEdge, calc_complements_1x1_is_correct)
{
  const size_t rows = 1;
  const size_t cols = 1;

  Matrix expected = Matrix(rows, cols);
  expected(0, 0) = 1;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 142.53;

  Matrix actual = a.CalcComplements();
  EXPECT_TRUE(actual.Equal(expected));
}

TEST_F(MatrixMathTestsEdge, determinant_3x3_zero_is_correct)
{
  const size_t rows = 3;
  const size_t cols = 3;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1;
  a(0, 1) = 53;
  a(0, 2) = 89;
  a(2, 0) = 62;
  a(2, 1) = 34;
  a(2, 2) = 4;

  double expected = 0.0;
  double actual = a.Determinant();
  EXPECT_NEAR(actual, expected, TestsEPS);
}

TEST_F(MatrixMathTestsEdge, inverse_1x1_is_correct)
{
  const size_t rows = 1;
  const size_t cols = 1;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1431.12312331;

  Matrix actual = a.Inverse();
  EXPECT_TRUE(actual(0, 0) == (1.0 / a(0, 0)));
}

/* ANOMALY */

class MatrixMathTestsAnomaly : public testing::Test
{
};

TEST_F(MatrixMathTestsAnomaly, calc_complements_not_square_throws)
{
  const size_t rows_a = 20;
  const size_t cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);

  EXPECT_THROW({ a.CalcComplements(); }, std::domain_error);
}

TEST_F(MatrixMathTestsAnomaly, determinant_not_square_throws)
{
  const size_t rows_a = 20;
  const size_t cols_a = 10;
  Matrix a = Matrix(rows_a, cols_a);

  EXPECT_THROW({ a.Determinant(); }, std::domain_error);
}

TEST_F(MatrixMathTestsAnomaly, inverse_zero_det_throws)
{
  const size_t rows_a = 3;
  const size_t cols_a = 3;
  Matrix a = Matrix(rows_a, cols_a);

  a(0, 0) = 2.0;
  a(0, 1) = 5.0;
  a(0, 2) = 7.0;
  a(2, 0) = 5.0;
  a(2, 1) = -2.0;
  a(2, 2) = -3.0;

  EXPECT_THROW({ a.Inverse(); }, std::domain_error);
}

TEST_F(MatrixMathTestsAnomaly, inverse_not_square_throws)
{
  const size_t rows_a = 3;
  const size_t cols_a = 2;
  Matrix a = Matrix(rows_a, cols_a);

  EXPECT_THROW({ a.Inverse(); }, std::domain_error);
}
