//#include "CommandBase.h"

//#include "Commands/DriveTrain/DriveToGear.h"
#include <Commands/DriveTrain/DriveToGearPost.h>

DriveToGearPost::DriveToGearPost()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(CommandBase::drivetrain.get());
}

// Called just before this Command runs the first time
void DriveToGearPost::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveToGearPost::Execute() {
	CommandBase::drivetrain.get()->DriveToGear();
}

// Make this return true when this Command no longer needs to run execute()
bool DriveToGearPost::IsFinished() {
	if(CommandBase::drivetrain.get()->_XPID->GetError() < 1.0 && CommandBase::drivetrain.get()->_YPID->GetError() < 1.0)
		return false;
	else
		return true;
}

// Called once after isFinished returns true
void DriveToGearPost::End() {
	CommandBase::drivetrain.get()->Drive(0.0, 0.0, 0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveToGearPost::Interrupted() {

}
