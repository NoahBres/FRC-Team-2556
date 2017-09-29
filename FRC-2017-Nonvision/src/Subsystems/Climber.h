#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "CANTalon.h"

class Climber:public Subsystem{
	private:

	public:
		std::unique_ptr<CANTalon> _ClimberMotor;

		Climber();
		void InitDefaultCommand();
		void Set(double Power);
};

#endif  // Climber_H
