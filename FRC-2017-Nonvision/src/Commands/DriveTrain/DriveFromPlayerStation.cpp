#include "DriveFromPlayerStation.h"

DriveFromPlayerStation::DriveFromPlayerStation(int playerStation, int gear) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(CommandBase::drivetrain.get());
	SetTimeout(5);
	PS = playerStation;
	gearPos = gear;
}

// Called just before this Command runs the first time
void DriveFromPlayerStation::Initialize() {
	//_PlayerStations = {-3, 0, 3};
	//_Gears = {-2.7, 0, 2.7};
}

// Called repeatedly when this Command is scheduled to run
void DriveFromPlayerStation::Execute() {
	CommandBase::drivetrain.get()->Drive((_PlayerStations[PS - 1] - _Gears[gearPos - 1]) / 5.7, (gearPos % 2) == 0 ? 1 : 2, 0.0, 0.0);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveFromPlayerStation::IsFinished() {
	return IsTimedOut();;
}

// Called once after isFinished returns true
void DriveFromPlayerStation::End() {
	CommandBase::drivetrain.get()->Drive(0.0, 0.0, 0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveFromPlayerStation::Interrupted() {

}
