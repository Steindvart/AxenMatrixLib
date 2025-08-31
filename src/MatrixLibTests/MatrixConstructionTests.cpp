#include "TestsSuite.h"

using namespace tests;

/* NORMAL */

class MatrixConstructionTestsNormal : public testing::Test
{
};

TEST_F(MatrixConstructionTestsNormal, default_construction_is_correct)
{
  Matrix a = Matrix();

  EXPECT_EQ(a.GetCols(), 1);
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a(0, 0), 0);
}

TEST_F(MatrixConstructionTestsNormal, params_construction_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);
  Matrix b = Matrix(rows, cols);

  EXPECT_EQ(a.GetRows(), rows);
  EXPECT_EQ(a.GetCols(), cols);
  EXPECT_TRUE(a.Equal(b));
}

TEST_F(MatrixConstructionTestsNormal, copy_construction_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b(a);

  EXPECT_EQ(b.GetRows(), rows);
  EXPECT_EQ(b.GetCols(), cols);
  EXPECT_TRUE(a.Equal(b));
}

TEST_F(MatrixConstructionTestsNormal, move_construction_is_correct)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix check = a;

  Matrix b(std::move(a));

  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
  EXPECT_EQ(b.GetRows(), rows);
  EXPECT_EQ(b.GetCols(), cols);
  EXPECT_TRUE(b.Equal(check));
}

/* EDGE */

class MatrixConstructionTestsEdge : public testing::Test
{
};

TEST_F(MatrixConstructionTestsEdge, params_construction_big_size_is_correct)
{
  const size_t rows = 10000;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);
  Matrix b = Matrix(rows, cols);

  EXPECT_EQ(a.GetCols(), cols);
  EXPECT_EQ(a.GetRows(), rows);
  EXPECT_TRUE(a.Equal(b));
}

/* ANOMALY */

class MatrixConstructionTestsAnomaly : public testing::Test
{
};

TEST_F(MatrixConstructionTestsAnomaly, params_construction_zero_rows_throws)
{
  const size_t rows = 0;
  const size_t cols = 10;
  EXPECT_THROW({ Matrix a = Matrix(rows, cols); }, std::invalid_argument);
}

TEST_F(MatrixConstructionTestsAnomaly, params_construction_zero_cols_throws)
{
  const size_t rows = 10;
  const size_t cols = 0;
  EXPECT_THROW({ Matrix a = Matrix(rows, cols); }, std::invalid_argument);
}
