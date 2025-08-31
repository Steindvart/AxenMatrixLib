#include <gtest/gtest.h>

#include "TestsSuite.h"

using namespace axen;

/* NORMAL */

TEST(utilsIsDoublesEq, eq0Normal)
{
  const double a = 1.0;
  const double b = 1.0;
  const double EPS = 1e-2;

  EXPECT_EQ(utils::IsDoublesEq(a, b, EPS), true);
}

TEST(utilsIsDoublesEq, eq1Normal)
{
  const double a = 0.0000006;
  const double b = 0.0000006;
  const double EPS = 1e-7;

  EXPECT_EQ(utils::IsDoublesEq(a, b, EPS), true);
}

TEST(utilsIsDoublesEq, neq0Normal)
{
  const double a = 0.9;
  const double b = 1.0;
  const double EPS = 1e-2;

  EXPECT_EQ(utils::IsDoublesEq(a, b, EPS), false);
}

TEST(utilsIsDoublesEq, neq1Normal)
{
  const double a = 0.0004001;
  const double b = 0.0000006;
  const double EPS = 1e-7;

  EXPECT_EQ(utils::IsDoublesEq(a, b, EPS), false);
}

/* EDGE */

TEST(utilsIsDoublesEq, downEpsEqEdge)
{
  const double a = 0.000000006;
  const double b = 0.00000006;
  const double EPS = 1e-7;

  EXPECT_EQ(utils::IsDoublesEq(a, b, EPS), true);
}

TEST(utilsIsDoublesEq, bigNumEqEdge)
{
  const double a = 764535435432234.000006;
  const double b = 764535435432234.000006;
  const double EPS = 1e-7;

  EXPECT_EQ(utils::IsDoublesEq(a, b, EPS), true);
}

TEST(utilsIsDoublesEq, bigEpsEqEdge)
{
  const double a = 0.000000006;
  const double b = 0.000000006;
  const double EPS = 1e-9;

  EXPECT_EQ(utils::IsDoublesEq(a, b, EPS), true);
}

TEST(utilsIsDoublesEq, bigEpsNeqEdge)
{
  const double a = 0.000000016;
  const double b = 0.000000006;
  const double EPS = 1e-9;

  EXPECT_EQ(utils::IsDoublesEq(a, b, EPS), false);
}

/* ANOMALY */

TEST(utilsIsDoublesEq, veryBigEpsEqAnomaly)
{
  const double a = 166.1536;
  const double b = 144.6743;
  const double EPS = 100;

  EXPECT_EQ(utils::IsDoublesEq(a, b, EPS), true);
}

TEST(utilsIsDoublesEq, veryBigEpsNeqTestAnomaly)
{
  const double a = 2166.1536;
  const double b = 144.6743;
  const double EPS = 100;

  EXPECT_EQ(utils::IsDoublesEq(a, b, EPS), false);
}
