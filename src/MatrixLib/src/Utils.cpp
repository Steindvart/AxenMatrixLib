#include "Utils.h"

#include <cmath>
#include <cstdlib>

// @todo - make as sepatate header only library

bool utils::IsDoublesEq(double a, double b, double EPS)
{
  return (fabs(a - b) < EPS);
}

double utils::GetRandom(double min, double max)
{
  double val = (double) rand() / RAND_MAX;
  return min + val * (max - min);
}

bool utils::IsEven(int n)
{
  return ((n % 2) == 0);
}

void utils::FillRandom(Matrix& matrix, double min, double max)
{
  for (size_t i = 0; i < matrix.GetRows(); i++)
  {
    for (size_t j = 0; j < matrix.GetCols(); j++)
    {
      matrix(i, j) = GetRandom(min, max);
    }
  }
}
