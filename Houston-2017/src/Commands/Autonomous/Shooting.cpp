#include "Shooting.h"

Shooting::Shooting(float timeout, float shooterPower, float tankPower) {
	Requires(CommandBase::shooter.get());
	SetTimeout(timeout);

	_ShooterPower = shooterPower;
	_TankPower = tankPower;
}

// Called just before this Command runs the first time
void Shooting::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Shooting::Execute() {
	shooter->Set(_ShooterPower, _TankPower);
}

// Make this return true when this Command no longer needs to run execute()
bool Shooting::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void Shooting::End() {
	shooter->Set(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shooting::Interrupted() {

}
