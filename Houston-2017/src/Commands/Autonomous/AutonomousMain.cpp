#include "AutonomousMain.h"
#include <thread>

AutonomousMain::AutonomousMain(){
	AddSequential(new Shooting(0.0, 0.0, 0.0));
	switch((int)SmartDashboard::GetNumber("DB/Slider 0", 0.0)){
	case 0:
		if(DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kBlue){
			AddSequential(new Drive(0.8,0.0,-0.,0.0));
		}

		break;
	}
	/*case 0:
		// shooting
		if(DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kBlue){
			AddSequential(new Drive(1.0, 0.0, -0.2, 0.0));

			AddSequential(new Shooting(7.0, 0.6, -0.4));

			AddParallel(new Shooting(6.6, 0.6, -0.4));

			AddSequential(new Drive(2.6, 0.8, 0.1, 0.025));

		} else if(DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kRed){
			AddSequential(new Shooting(12.0, 0.6, -0.4));

			AddSequential(new Drive(2.6, 0.8, 0.0, 0.025));
		}
		break;
	case 1:
		// drive forward
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
	case 3:
		if(DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kBlue){
					AddSequential(new Drive(1.0, 0.0, -0.2, 0.0));

					AddSequential(new Shooting(11.0, 0.6, -0.4));

					AddSequential(new Drive(2.6, 0.8, 0.0, 0.025));

				} else if(DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kRed){
					AddSequential(new Shooting(4.0, 0.6, -0.9));

					AddSequential(new Drive(2.6, 1.0, 0.25, 0.0));
					//AddSequential(new GearIntake());
				}
		break;
	}*/

	//AddSequential(new Drive(1.5, 0.0, -0.5, 0.0));
	/*AddSequential(new DriveFromPlayerStation(SmartDashboard::GetNumber("PlayerStation", 1.0), SmartDashboard::GetNumber("Gear", 1.0)));

	if(SmartDashboard::GetNumber("Gear", 0.0) != 2)
		AddSequential(new Drive(1, 0, 0, 0.25));

	AddSequential(new DriveToGearPost());
	AddSequential(new Drive(2, 0.0, 0.5, 0.0));
	AddSequential(new Drive(2, 0.0, -0.5, 0.0));

\
	if(SmartDashboard::GetNumber("Gear", 0.0) == 2){
		AddSequential(new Drive(3, 0.7, 0, 0.0));
		AddSequential(new Drive(2, 0.0, 0.5, 0.0));
	}*/
}
