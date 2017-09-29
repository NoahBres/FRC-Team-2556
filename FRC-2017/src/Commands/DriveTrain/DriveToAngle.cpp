#include <RobotMap.h>
#include <Commands/DriveTrain/DriveToAngle.h>

DriveToAngle::DriveToAngle(float timeout, float xPower, float yPower, float angle){
	Requires(CommandBase::drivetrain.get());
	SetTimeout(timeout);
	_xPower = xPower;
	_yPower = yPower;
	_Angle = angle;
}

void DriveToAngle::Initialize(){

}

void DriveToAngle::Execute(){
#ifdef NAVX
	drivetrain.get()->Drive(_xPower, _yPower, (NavX->GetYaw() - _Angle) * -0.05, 0.0);
#else
	drivetrain.get()->Drive(_xPower, _yPower, 0.0, 0.0);
#endif
}

bool DriveToAngle::IsFinished(){
	return IsTimedOut();
}

void DriveToAngle::End(){
	CommandBase::drivetrain.get()->DriveWithAngle(0.0, 0.0, 0.0, 0.0);
}

void DriveToAngle::Interrupted(){

}
