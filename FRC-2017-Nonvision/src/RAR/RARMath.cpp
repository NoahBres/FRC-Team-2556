/*
 * Name: RARMath.cpp
 * Authors: Andrew Parmer
 * Dates: 2015-09-29
 * Description: Adds helpful math functions
 */

#include "RARMath.h"

double DeadSens(double Value, double Deadzone, double Sensitivity){
	return (Value < Deadzone) && (Value > -Deadzone) ? 0 : Sensitivity * std::pow(Value, 3) + (1 - Sensitivity) * Value;
}

template <typename Number>
Number Clamp(Number Value, Number Min, Number Max){
	return std::max(Min, std::min(Value, Max));
}

template int Clamp<int>(int Value, int Min, int Max);
template float Clamp<float>(float Value, float Min, float Max);
template double Clamp<double>(double Value, double Min, double Max);
