/*
 * Name: RARMath.h
 * Authors: Andrew Parmer
 * Dates: 2015-09-29
 * Description: Adds helpful math functions
 */

#ifndef RARMath
#define RARMath

#include <cmath>
#include <algorithm>

double DeadSens(double Value, double Deadzone, double Sensitivity);

template <typename Number>
Number Clamp(Number Value, Number Min, Number Max);

#endif
