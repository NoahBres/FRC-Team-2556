#include <Commands/DriveTrain/DriveToAngle.h>

DriveToAngle::DriveToAngle():
	frc::PIDCommand(0.0, 0.0, 0.0){
	Requires(CommandBase::drivetrain.get());
}

void DriveToAngle::Initialize(){

}

void DriveToAngle::Execute(){

}

void DriveToAngle::PIDWrite(double Output){
	CommandBase::drivetrain.get()->Drive(0.0, 0.0, Output, 0.0);
}

double DriveToAngle::PIDGet(){
	return 0.0;//NavX->GetYaw();
}

bool DriveToAngle::IsFinished(){
	return false;
}

void DriveToAngle::End(){
	CommandBase::drivetrain.get()->Drive(0.0, 0.0, 0.0, 0.0);
}

void DriveToAngle::Interrupted(){

}
