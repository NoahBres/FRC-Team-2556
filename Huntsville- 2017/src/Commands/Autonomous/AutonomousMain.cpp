#include "AutonomousMain.h"

AutonomousMain::AutonomousMain(){
	AddSequential(new Shooting(0.0, 0.0, 0.0));
	switch((int)SmartDashboard::GetNumber("DB/Slider 0", 0.0)){
	case 0:
		if(DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kBlue){
			AddSequential(new Drive(1.0, 0.0, -0.2, 0.0));
			// changed shoot time (old time 11.0)
			AddSequential(new Shooting(10.0, 0.6, -0.4));
			// changed drive time (old time 2.6)
			AddSequential(new Drive(2.8, 0.8, 0.1, 0.025));
		} else if(DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kRed){
			AddSequential(new Shooting(12.0, 0.6, -0.4));

			AddSequential(new Drive(2.6, 0.8, 0.0, 0.025));
		}
		break;
	case 1:
		if(DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kBlue){
			AddSequential(new Drive(2.0, 0.0, 0.5, 0.0));
			AddSequential(new Drive(1.25, 0.5, 0.0, 0.0));
		} else if(DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kRed){
			AddSequential(new Drive(2.0, 0.0, -0.5, 0.0));
			AddSequential(new Drive(1.25, 0.5, 0.0, 0.0));
		}
		break;
	case 2:
		break;
	}

	//AddSequential(new Drive(1.5, 0.0, -0.5, 0.0));
	/*AddSequential(new DriveFromPlayerStation(SmartDashboard::GetNumber("PlayerStation", 1.0), SmartDashboard::GetNumber("Gear", 1.0)));

	if(SmartDashboard::GetNumber("Gear", 0.0) != 2)
		AddSequential(new Drive(1, 0, 0, 0.25));

	AddSequential(new DriveToGearPost());
	AddSequential(new Drive(2, 0.0, 0.5, 0.0));
	AddSequential(new Drive(2, 0.0, -0.5, 0.0));


	if(SmartDashboard::GetNumber("Gear", 0.0) == 2){
		AddSequential(new Drive(3, 0.7, 0, 0.0));
		AddSequential(new Drive(2, 0.0, 0.5, 0.0));
	}*/
}
