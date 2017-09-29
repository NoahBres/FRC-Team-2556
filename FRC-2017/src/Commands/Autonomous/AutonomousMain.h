#ifndef AutonomousMain_H
#define AutonomousMain_H

#include <Commands/DriveTrain/DriveToGearPost.h>
#include <Commands/DriveTrain/DriveFromPlayerStation.h>
#include <Commands/DriveTrain/Drive.h>
#include <Commands/DriveTrain/DriveToAngle.h>
#include <Commands/Autonomous/Shooting.h>
#include "WPILib.h"
#include "Commands/CommandGroup.h"

class AutonomousMain: public CommandGroup{
	public:
		AutonomousMain();
};

#endif
