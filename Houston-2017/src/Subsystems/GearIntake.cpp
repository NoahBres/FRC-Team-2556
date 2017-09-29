#include "GearIntake.h"
#include "../RobotMap.h"

GearIntake::GearIntake() : Subsystem("GearIntake"){
	_IntakeSolenoid.reset(new frc::DoubleSolenoid(PCM, 0, 1));
}

void GearIntake::InitDefaultCommand(){

}

void GearIntake::Set(frc::DoubleSolenoid::Value Direction){
	_IntakeSolenoid->Set(Direction);
}
