#include "BallIntake.h"
#include "../RobotMap.h"

BallIntake::BallIntake():Subsystem("BallIntake"){
	_IntakeMotor.reset(new CANTalon(BALL_MOTOR));
}

void BallIntake::InitDefaultCommand(){

}

void BallIntake::Set(double IntakePower){
	_IntakeMotor->Set(IntakePower);
}
