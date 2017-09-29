#ifndef DriveTrain_H
#define DriveTrain_H

#include "../RobotMap.h"

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"
#include "PIDSourceD.h"

#ifdef NAVX
#include "IMU.h"

extern std::unique_ptr<IMU> NavX;
#endif

class DriveTrain:public Subsystem, frc::PIDOutput{
	private:
		std::shared_ptr<NetworkTable> table;
		PIDSourceD _XPIDSource;
		PIDSourceD _YPIDSource;

		frc::LiveWindow *LW;
	public:
		std::unique_ptr<CANTalon> _FrontLeft;
		std::unique_ptr<CANTalon> _FrontRight;
		std::unique_ptr<CANTalon> _BackLeft;
		std::unique_ptr<CANTalon> _BackRight;

		std::unique_ptr<frc::RobotDrive> _Drive;

#ifdef NAVX
		std::unique_ptr<frc::PIDController> _AngleController;
#endif
		std::unique_ptr<frc::PIDController> _XPID;
		std::unique_ptr<frc::PIDController> _YPID;

		DriveTrain();
		void InitDefaultCommand();
		void Drive(double X, double Y, double Rotation, double GyroAngle);
		void DriveWithAngle(double X, double Y, double dSetPoint, double GyroAngle);
		void SetPID(float P, float I, float D, float F);
		void PIDWrite(double Output);
		void DriveToGear();
		void DriveToGoal();

};

#endif
