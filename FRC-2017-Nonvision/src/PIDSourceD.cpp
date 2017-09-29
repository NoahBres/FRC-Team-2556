#include "PIDSourceD.h"

PIDSourceD::PIDSourceD(double value){
	_Value = value;
}

void PIDSourceD::SetValue(double value){
	_Value = value;
}

double PIDSourceD::PIDGet(){
	return _Value;
}

void PIDSourceD::SetPIDSourceType(PIDSourceType pidSource){}
