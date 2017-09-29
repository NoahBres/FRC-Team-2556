#ifndef BallIntake_H
#define BallIntake_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "CANTalon.h"

class BallIntake:public Subsystem{
	private:

	public:
		std::unique_ptr<CANTalon> _IntakeMotor;

		BallIntake();
		void InitDefaultCommand();
		void Set(double IntakePower);
};

#endif  // BallIntake_H
