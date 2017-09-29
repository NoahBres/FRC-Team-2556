#include "DriveTrain.h"
#include "../RobotMap.h"

DriveTrain::DriveTrain():Subsystem("DriveTrain"){
	_FrontLeft.reset(new CANTalon(FRONT_LEFT_MOTOR));
	_FrontRight.reset(new CANTalon(FRONT_RIGHT_MOTOR));
	_BackLeft.reset(new CANTalon(BACK_LEFT_MOTOR));
	_BackRight.reset(new CANTalon(BACK_RIGHT_MOTOR));

	_FrontRight->SetInverted(true);
	_BackRight->SetInverted(true);

	/*_FrontLeft->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	_FrontRight->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	_BackLeft->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	_BackRight->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);*/

	/*_FrontLeft->SetVoltageRampRate(10.0);
	_FrontRight->SetVoltageRampRate(10.0);
	_BackLeft->SetVoltageRampRate(10.0);
	_BackRight->SetVoltageRampRate(10.0);*/

	_Drive.reset(new frc::RobotDrive(_FrontLeft.get(), _BackLeft.get(), _FrontRight.get(), _BackRight.get()));

	//_AngleController.reset(new frc::PIDController(0.0, 0.0, 0.0, NavX.get(), this));
	_XPID.reset(new frc::PIDController(0.0, 0.0, 0.0, &_XPIDSource, this));
	_YPID.reset(new frc::PIDController(0.0, 0.0, 0.0, &_YPIDSource, this));

	_XPID->SetSetpoint(0.0);
	_YPID->SetSetpoint(0.0);

	table = NetworkTable::GetTable("Vision");

	/*LW = LiveWindow::GetInstance();
	LW->AddActuator("DriveTrain", "PID", _AngleController.get());
	LW->SetEnabled(true);*/
}

void DriveTrain::InitDefaultCommand(){

}

void DriveTrain::Drive(double X, double Y, double Rotation, double GyroAngle){
	_Drive->MecanumDrive_Cartesian(X, Y, Rotation, GyroAngle);
}

void DriveTrain::DriveWithAngle(double X, double Y, double dSetPoint, double GyroAngle){
	//_AngleController->SetSetpoint(_AngleController->GetSetpoint() + dSetPoint);//_AngleController->GetSetpoint() + dSetPoint);
	//_Drive->MecanumDrive_Cartesian(X, Y, _AngleController->Get(), GyroAngle);
}

void DriveTrain::PIDWrite(double Output){

}

void DriveTrain::DriveToGear(){
	_XPID->SetSetpoint(0.0);
	_YPID->SetSetpoint(0.0);

	_XPIDSource.SetValue(table->GetNumber("X", 0.0));
	_YPIDSource.SetValue(table->GetNumber("Y", 0.0));

	_Drive->MecanumDrive_Cartesian(_XPID->Get(), _YPID->Get(), 0.0, 0.0);
}

void DriveTrain::DriveToGoal(){

	_XPID->SetSetpoint(0.0);
	_YPID->SetSetpoint(0.0);

	_XPIDSource.SetValue(table->GetNumber("X", 0.0));
	_YPIDSource.SetValue(table->GetNumber("Y", 0.0));

	_Drive->MecanumDrive_Cartesian(_XPID->Get(), _YPID->Get(), 0.0, 0.0);
}
