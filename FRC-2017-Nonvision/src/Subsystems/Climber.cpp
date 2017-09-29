#include "Climber.h"
#include "../RobotMap.h"

Climber::Climber():Subsystem("Climber"){
	_ClimberMotor.reset(new CANTalon(CLIMBER_MOTOR));
}

void Climber::InitDefaultCommand(){

}

void Climber::Set(double Power){
	_ClimberMotor->Set(Power);
}
