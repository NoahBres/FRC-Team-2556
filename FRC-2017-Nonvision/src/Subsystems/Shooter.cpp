#include "Shooter.h"
#include "../RobotMap.h"
#include <SmartDashboard/SmartDashboard.h>

Shooter::Shooter():Subsystem("Shooter"){
	_ShooterMotor.reset(new CANTalon(SHOOTER_MOTOR));
	_TankMotor.reset(new Spark(TANK_MOTOR));
	_CameraServo.reset(new Servo(CAMERA_SERVO));

	/*_ShooterMotor->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	_ShooterMotor->SetControlMode(frc::CANSpeedController::kSpeed);
	_ShooterMotor->SetClosedLoopOutputDirection(true);
	_ShooterMotor->SetPID(0.0, 0.0, 0.0, 0.0);*/
	/*_ShooterMotor->SetP(0.05);
	_ShooterMotor->SetI(0.0004);
	_ShooterMotor->SetD(0.1);*/
}

void Shooter::InitDefaultCommand(){

}

void Shooter::Set(double ShooterSpeed, double TankSpeed){
	_ShooterMotor->Set(ShooterSpeed/* * -6100*/);

	SmartDashboard::PutNumber("Error", _ShooterMotor->GetClosedLoopError());
	SmartDashboard::PutNumber("Speed", _ShooterMotor->GetSpeed());
	SmartDashboard::PutNumber("Shooter Set", _ShooterMotor->GetSetpoint());

	_TankMotor->Set(TankSpeed);
}

void Shooter::SetServo(float Pos){
	_CameraServo->Set(Pos);
}
