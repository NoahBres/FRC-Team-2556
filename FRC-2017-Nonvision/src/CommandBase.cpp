#include "CommandBase.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
std::unique_ptr<DriveTrain> CommandBase::drivetrain;
std::unique_ptr<BallIntake> CommandBase::ballintake;
std::unique_ptr<GearIntake> CommandBase::gearintake;
std::unique_ptr<Climber> CommandBase::climber;
std::unique_ptr<Shooter> CommandBase::shooter;
std::unique_ptr<OI> CommandBase::oi;

CommandBase::CommandBase(const std::string &name):Command(name){
}

CommandBase::CommandBase():Command(){
}

void CommandBase::init(){
	drivetrain.reset(new DriveTrain());
	ballintake.reset(new BallIntake());
	gearintake.reset(new GearIntake());
	climber.reset(new Climber());
	shooter.reset(new Shooter());

	oi.reset(new OI());
}
