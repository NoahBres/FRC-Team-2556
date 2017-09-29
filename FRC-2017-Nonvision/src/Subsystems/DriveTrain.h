#ifndef DriveTrain_H
#define DriveTrain_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"
#include "IMU.h"
#include "PIDSourceD.h"

extern std::unique_ptr<IMU> NavX;

class DriveTrain:public Subsystem, frc::PIDOutput{
	private:
		std::shared_ptr<NetworkTable> table;
		PIDSourceD _XPIDSource;
		PIDSourceD _YPIDSource;

		//frc::LiveWindow *LW;
	public:
		std::unique_ptr<CANTalon> _FrontLeft;
		std::unique_ptr<CANTalon> _FrontRight;
		std::unique_ptr<CANTalon> _BackLeft;
		std::unique_ptr<CANTalon> _BackRight;

		std::unique_ptr<frc::RobotDrive> _Drive;

		std::unique_ptr<frc::PIDController> _AngleController;
		std::unique_ptr<frc::PIDController> _XPID;
		std::unique_ptr<frc::PIDController> _YPID;

		DriveTrain();
		void InitDefaultCommand();
		void Drive(double X, double Y, double Rotation, double GyroAngle);
		void DriveWithAngle(double X, double Y, double dSetPoint, double GyroAngle);
		void PIDWrite(double Output);
		void DriveToGear();
		void DriveToGoal();

};

#endif
