#include <Commands/DriveTrain/Drive.h>

Drive::Drive(float timeout, float xPower, float yPower, float rotation) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(CommandBase::drivetrain.get());
	SetTimeout(timeout);
	_xPower = xPower;
	_yPower = yPower;
	_Rotation = rotation;
}

// Called just before this Command runs the first time
void Drive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
	CommandBase::drivetrain.get()->Drive(_xPower, _yPower, _Rotation, 0.0);
}

// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void Drive::End() {
	CommandBase::drivetrain.get()->Drive(0.0, 0.0, 0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {

}
