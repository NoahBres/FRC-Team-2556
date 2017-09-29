#ifndef DriveToAngle_H
#define DriveToAngle_H

#include "CommandBase.h"
#include "WPILib.h"
#include "RAR/RARMath.h"
#include "IMU.h"

extern std::unique_ptr<IMU> NavX;

class DriveToAngle:frc::PIDCommand{
	public:
		DriveToAngle();
		void Initialize();
		void Execute();
		void PIDWrite(double Output);
		double PIDGet();
		bool IsFinished();
		void End();
		void Interrupted();
};

#endif
