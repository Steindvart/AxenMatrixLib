#include "TestsSuite.h"

using namespace tests;

/* NORMAL */

class MatrixLogicTestsNormal : public testing::Test
{
};

TEST_F(MatrixLogicTestsNormal, same_matrix_is_equal)
{
  const size_t rows = 20;
  const size_t cols = 10;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1;

  Matrix b = Matrix(rows, cols);
  b(0, 0) = 1;

  EXPECT_TRUE(a.Equal(b));
}

TEST_F(MatrixLogicTestsNormal, copied_matrix_is_equal)
{
  const size_t rows = 20;
  const size_t cols = 10;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = a;

  EXPECT_TRUE(a.Equal(b));
}

TEST_F(MatrixLogicTestsNormal, different_matrix_is_not_equal)
{
  const size_t rows = 20;
  const size_t cols = 10;

  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);
  a(0, 0) = 1;

  Matrix b = Matrix(rows, cols);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);
  b(0, 0) = 2;

  EXPECT_FALSE(a.Equal(b));
}

TEST_F(MatrixLogicTestsNormal, by_operator_same_matrix_is_equal)
{
  const size_t rows = 20;
  const size_t cols = 10;

  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1;

  Matrix b = Matrix(rows, cols);
  b(0, 0) = 1;

  EXPECT_TRUE(a == b);
}

TEST_F(MatrixLogicTestsNormal, by_operator_copied_matrix_is_equal)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = a;

  EXPECT_TRUE(a == b);
}

TEST_F(MatrixLogicTestsNormal, by_operator_different_matrix_is_not_equal)
{
  const size_t rows = 20;
  const size_t cols = 10;
  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = Matrix(rows, cols);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  EXPECT_FALSE(a == b);
}

/* EDGE */

class MatrixLogicTestsEdge : public testing::Test
{
};

TEST_F(MatrixLogicTestsEdge, copied_large_matrix_is_equal)
{
  const size_t rows = 100;
  const size_t cols = 50;
  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = a;

  EXPECT_TRUE(a.Equal(b));
}

TEST_F(MatrixLogicTestsEdge, different_large_matrix_is_not_equal)
{
  const size_t rows = 100;
  const size_t cols = 50;
  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);
  a(0, 0) = 1;

  Matrix b = Matrix(rows, cols);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);
  b(0, 0) = 2;

  EXPECT_FALSE(a.Equal(b));
}

TEST_F(MatrixLogicTestsEdge, different_overflow_eps_matrix_is_equal)
{
  const size_t rows = 2;
  const size_t cols = 2;
  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1.0000000688888;
  a(0, 1) = 45352.64645;
  a(1, 0) = 52.000003;
  a(1, 1) = 0.000001;

  Matrix b = Matrix(rows, cols);
  b(0, 0) = 1.0000000611111;
  b(0, 1) = 45352.64645;
  b(1, 0) = 52.000003;
  b(1, 1) = 0.000001;

  EXPECT_TRUE(a.Equal(b));
}

TEST_F(MatrixLogicTestsEdge, different_in_edge_eps_matrix_is_not_equal)
{
  const size_t rows = 2;
  const size_t cols = 2;
  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1.000000488888;
  a(0, 1) = 45352.64645;
  a(1, 0) = 52.000003;
  a(1, 1) = 0.000001;

  Matrix b = Matrix(rows, cols);
  b(0, 0) = 1.000000611111;
  b(0, 1) = 45352.64645;
  b(1, 0) = 52.000003;
  b(1, 1) = 0.000001;

  EXPECT_FALSE(a.Equal(b));
}

TEST_F(MatrixLogicTestsEdge, by_operator_copied_large_matrix_is_equal)
{
  const size_t rows = 100;
  const size_t cols = 50;
  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = a;

  EXPECT_TRUE(a == b);
}

TEST_F(MatrixLogicTestsEdge, by_operator_different_large_matrix_is_not_equal)
{
  const size_t rows = 100;
  const size_t cols = 50;
  Matrix a = Matrix(rows, cols);
  utils::FillRandom(a, FLT_MIN, FLT_MAX);

  Matrix b = Matrix(rows, cols);
  utils::FillRandom(b, FLT_MIN, FLT_MAX);

  EXPECT_FALSE(a == b);
}

TEST_F(MatrixLogicTestsEdge, by_operator_different_overflow_eps_matrix_is_equal)
{
  const size_t rows = 2;
  const size_t cols = 2;
  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1.0000000688888;
  a(0, 1) = 45352.64645;
  a(1, 0) = 52.000003;
  a(1, 1) = 0.000001;

  Matrix b = Matrix(rows, cols);
  b(0, 0) = 1.0000000611111;
  b(0, 1) = 45352.64645;
  b(1, 0) = 52.000003;
  b(1, 1) = 0.000001;

  EXPECT_TRUE(a == b);
}

TEST_F(MatrixLogicTestsEdge, by_operator_different_in_edge_eps_matrix_is_not_equal)
{
  const size_t rows = 2;
  const size_t cols = 2;
  Matrix a = Matrix(rows, cols);
  a(0, 0) = 1.000000488888;
  a(0, 1) = 45352.64645;
  a(1, 0) = 52.000003;
  a(1, 1) = 0.000001;

  Matrix b = Matrix(rows, cols);
  b(0, 0) = 1.000000611111;
  b(0, 1) = 45352.64645;
  b(1, 0) = 52.000003;
  b(1, 1) = 0.000001;

  EXPECT_FALSE(a == b);
}
