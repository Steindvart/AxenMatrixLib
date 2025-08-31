#pragma once

#include "Matrix.h"

namespace utils
{

double GetRandom(double min, double max);
bool IsDoublesEq(double a, double b, double EPS);
bool IsEven(int n);

void FillRandom(Matrix& m, double min, double max);

}  // namespace utils
