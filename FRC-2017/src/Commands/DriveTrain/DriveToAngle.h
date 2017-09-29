#ifndef DriveToAngle_H
#define DriveToAngle_H

#include "CommandBase.h"
#include "WPILib.h"
#include "RAR/RARMath.h"

#ifdef NAVX
#include "IMU.h"

extern std::unique_ptr<IMU> NavX;
#endif

class DriveToAngle:public CommandBase{
	private:
		double _xPower;
		double _yPower;
		double _Angle;
	public:
		DriveToAngle(float timeout, float xPower, float yPower, float angle);
		void Initialize();
		void Execute();
		bool IsFinished();
		void End();
		void Interrupted();
};

#endif
