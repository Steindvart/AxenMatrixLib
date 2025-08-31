#include "TestsSuite.h"

using namespace tests;
using namespace axen;

/* NORMAL */

class MatrixAccessTestsNormal : public testing::Test
{
};

TEST_F(MatrixAccessTestsNormal, assign_lvalue_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b;
  b = a;

  EXPECT_EQ(b.GetRows(), rows);
  EXPECT_EQ(b.GetCols(), cols);
  EXPECT_TRUE(a.Equal(b));
}

TEST_F(MatrixAccessTestsNormal, assign_rvalue_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix check = a;

  Matrix b;
  b = std::move(a);

  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
  EXPECT_EQ(b.GetRows(), rows);
  EXPECT_EQ(b.GetCols(), cols);
  EXPECT_TRUE(b.Equal(check));
}

TEST_F(MatrixAccessTestsNormal, get_set_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  const double val = 42.123;
  a(0, 0) = val;

  EXPECT_EQ(a(0, 0), val);
}

TEST_F(MatrixAccessTestsNormal, get_rows_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  EXPECT_EQ(a.GetRows(), rows);
}

TEST_F(MatrixAccessTestsNormal, get_cols_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  EXPECT_EQ(a.GetCols(), cols);
}

TEST_F(MatrixAccessTestsNormal, set_rows_up_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  const size_t newRows = 30;
  a.SetRows(newRows);

  EXPECT_EQ(a.GetRows(), newRows);
  EXPECT_EQ(a(22, 1), 0);
}

TEST_F(MatrixAccessTestsNormal, set_rows_down_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  const size_t newRows = 5;
  a.SetRows(newRows);

  EXPECT_EQ(a.GetRows(), newRows);
}

TEST_F(MatrixAccessTestsNormal, set_cols_up_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  const size_t newCols = 30;
  a.SetCols(newCols);

  EXPECT_EQ(a.GetCols(), newCols);
  EXPECT_EQ(a(1, 22), 0);
}

TEST_F(MatrixAccessTestsNormal, set_cols_down_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  const size_t newCols = 5;
  a.SetCols(newCols);

  EXPECT_EQ(a.GetCols(), newCols);
}

/* EDGE */

class MatrixAccessTestsEdge : public testing::Test
{
};

TEST_F(MatrixAccessTestsEdge, set_cols_big_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  const size_t newCols = 300;
  a.SetCols(newCols);

  EXPECT_EQ(a.GetCols(), newCols);
  EXPECT_EQ(a(1, 120), 0);
}

TEST_F(MatrixAccessTestsEdge, set_rows_big_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  const size_t newRows = 300;
  a.SetRows(newRows);

  EXPECT_EQ(a.GetRows(), newRows);
  EXPECT_EQ(a(120, 1), 0);
}

/* ANOMALY */

class MatrixAccessTestsAnomaly : public testing::Test
{
};

TEST_F(MatrixAccessTestsAnomaly, assign_lvalue_same_obj_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  a = a;

  EXPECT_EQ(a.GetRows(), rows);
  EXPECT_EQ(a.GetCols(), cols);
  EXPECT_TRUE(a.Equal(a));
}

TEST_F(MatrixAccessTestsAnomaly, assign_rvalue_same_obj_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix check = a;

  a = std::move(a);

  EXPECT_EQ(a.GetRows(), rows);
  EXPECT_EQ(a.GetCols(), cols);
  EXPECT_TRUE(a.Equal(check));
}

TEST_F(MatrixAccessTestsAnomaly, get_out_of_range_throws)
{
  const size_t rows = 20;
  const size_t cols = 10;
  const Matrix a = Matrix(rows, cols);

  EXPECT_THROW({ a(142, 0); }, std::out_of_range);

  EXPECT_THROW({ a(0, 142); }, std::out_of_range);
}

TEST_F(MatrixAccessTestsAnomaly, set_out_of_range_throws)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  EXPECT_THROW({ a(142, 0) = 42; }, std::out_of_range);

  EXPECT_THROW({ a(0, 142) = 111; }, std::out_of_range);
}

TEST_F(MatrixAccessTestsAnomaly, set_rows_zero_throws)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  const size_t newRows = 0;
  EXPECT_THROW({ a.SetRows(newRows); }, std::invalid_argument);
}

TEST_F(MatrixAccessTestsAnomaly, set_cols_zero_throws)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);

  const size_t newCols = 0;
  EXPECT_THROW({ a.SetCols(newCols); }, std::invalid_argument);
}
