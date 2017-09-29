#include "Commands/DriveTrain/DriveToGearPost.h" // BOB
#include "TeleopCommand.h"
#include <cmath>


TeleopCommand::TeleopCommand():
	_DriveMode(0),
	_SwitchFlag(false){
	Requires(drivetrain.get());
	Requires(ballintake.get());
	Requires(gearintake.get());
	Requires(climber.get());
	Requires(shooter.get());

	_Table = NetworkTable::GetTable("Vision");
	_Table->PutNumber("Camera", 1.0);
}

void TeleopCommand::Initialize(){

}

void TeleopCommand::Execute(){
	if(!_SwitchFlag && oi->Xbox1.get()->GetBumper(frc::XboxController::kLeftHand) && _Table->GetNumber("Camera", 0.0) != 0.0){
		_Table->PutNumber("Camera", _Table->GetNumber("Camera", 0.0) - 1.0);
		_SwitchFlag = true;
	}else if(!_SwitchFlag && oi->Xbox1.get()->GetBumper(frc::XboxController::kRightHand)){
		_Table->PutNumber("Camera", _Table->GetNumber("Camera", 0.0) + 1.0);
		_SwitchFlag = true;
	}else if(!oi->Xbox1.get()->GetBumper(frc::XboxController::kLeftHand) && !oi->Xbox1.get()->GetBumper(frc::XboxController::kRightHand)){
		_SwitchFlag = false;
	}

	if(oi->Xbox1.get()->GetAButton())
		_DriveMode = 0; // Front
	if(oi->Xbox1.get()->GetBButton())
		_DriveMode = -1; // Left
	if(oi->Xbox1.get()->GetYButton())
		_DriveMode = 1; // Right

	/*if(oi->Xbox1.get()->GetXButton())
		drivetrain.get()->DriveToGear();
	else*/
		drivetrain.get()->Drive(DeadSens(oi->Xbox1.get()->GetX(frc::XboxController::kLeftHand), 0.025, 0.85), DeadSens(oi->Xbox1.get()->GetY(frc::XboxController::kLeftHand), 0.025, 0.85), DeadSens(oi->Xbox1.get()->GetX(frc::XboxController::kRightHand), 0.025, 0.85), _DriveMode * 90.0);
	//drivetrain.get()->DriveWithAngle(DeadSens(oi->Xbox1.get()->GetX(frc::XboxController::kLeftHand), 0.025, 0.85), DeadSens(oi->Xbox1.get()->GetY(frc::XboxController::kLeftHand), 0.025, 0.85), DeadSens(oi->Xbox1.get()->GetX(frc::XboxController::kRightHand), 0.025, 0.85), _DriveMode * 90.0);

	//oi->Xbox1.get()->GetBumper(frc::XboxController::kRightHand) ? SmartDashboard::PutNumber("Camera", SmartDashboard::GetNumber("Camera", -1.0) + 1.0) : 0.0;
	//oi->Xbox1.get()->GetBumper(frc::XboxController::kLeftHand) ? SmartDashboard::PutNumber("Camera", SmartDashboard::GetNumber("Camera", 1.0) - 1.0) : 0.0;

	if(oi->Xbox2.get()->GetPOV() == 90)
		shooter.get()->SetServo(0);
	else if(oi->Xbox2.get()->GetPOV() == 0)
		shooter.get()->SetServo(0.5);
	else if(oi->Xbox2.get()->GetPOV() == 270)
		shooter.get()->SetServo(1);

	if(SmartDashboard::GetBoolean("Two Controllers?", true)) {
		shooter.get()->Set(oi->Xbox2.get()->GetBumper(frc::XboxController::kRightHand) ? 0.7 : 0.0, oi->Xbox2.get()->GetAButton() ? -0.5 : oi->Xbox2.get()->GetBButton() ? -0.25 : oi->Xbox2.get()->GetYButton() ? 0.5 : 0.0);
		ballintake.get()->Set(oi->Xbox2.get()->GetTriggerAxis(frc::XboxController::kRightHand) - oi->Xbox2.get()->GetTriggerAxis(frc::XboxController::kLeftHand));
		gearintake.get()->Set(oi->Xbox2.get()->GetXButton() ? frc::DoubleSolenoid::Value::kForward : frc::DoubleSolenoid::Value::kReverse);
		climber.get()->Set(-fabs(DeadSens(oi->Xbox2.get()->GetY(frc::XboxController::kLeftHand), 0.025, 1.0)));
	} else {
		shooter.get()->Set(0.0, oi->Xbox1.get()->GetXButton() ? 0.5 : 0.0);
		ballintake.get()->Set(oi->Xbox1.get()->GetTriggerAxis(frc::XboxController::kRightHand) - oi->Xbox1.get()->GetTriggerAxis(frc::XboxController::kLeftHand));
		gearintake.get()->Set(oi->Xbox1.get()->GetXButton() ? frc::DoubleSolenoid::Value::kForward : frc::DoubleSolenoid::Value::kReverse);
		climber.get()->Set(oi->Xbox1.get()->GetBumper(frc::XboxController::kRightHand) ? 1.0 : 0.0);
	}
}


bool TeleopCommand::IsFinished(){
	return false;
}

void TeleopCommand::End(){
	drivetrain.get()->Drive(0.0, 0.0, 0.0, 0.0);
	shooter.get()->Set(0.0, 0.0);
	ballintake.get()->Set(0.0);
	gearintake.get()->Set(frc::DoubleSolenoid::kOff);
	climber.get()->Set(0.0);
}

void TeleopCommand::Interrupted(){

}

int TeleopCommand::GetDriveMode(){
	return _DriveMode;
}
