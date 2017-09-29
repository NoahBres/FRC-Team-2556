#ifndef GearIntake_H
#define GearIntake_H

#include <Commands/Subsystem.h>
#include "WPILib.h"

class GearIntake:public Subsystem{
	private:

	public:
		std::unique_ptr<frc::DoubleSolenoid> _IntakeSolenoid;

		GearIntake();
		void InitDefaultCommand();
		void Set(frc::DoubleSolenoid::Value Direction);
};

#endif  // GearIntake_H
