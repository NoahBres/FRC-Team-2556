#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "CommandBase.h"
#include "RobotMap.h"

#include "Commands/Autonomous/AutonomousMain.h"
#include "Commands/Teleoperated/TeleopCommand.h"

#include "IMU.h"

std::unique_ptr<IMU> NavX;

class Robot:public frc::IterativeRobot{
	private:
		std::unique_ptr<frc::Command> AutonomousC;
		std::unique_ptr<TeleopCommand> TeleopC;
		std::unique_ptr<frc::Compressor> Comp;
		std::shared_ptr<NetworkTable> Table;
		frc::Preferences *prefs;

		std::unique_ptr<Talon> _LEDs;
		//frc::SendableChooser<frc::Command*> chooser;
	public:
		void RobotInit() override{
			CommandBase::init();

			/*chooser.AddDefault("Default Auto", new ExampleCommand());
			chooser.AddObject("My Auto", new MyAutoCommand());
			frc::SmartDashboard::PutData("Auto Modes", &chooser);*/

			TeleopC.reset(new TeleopCommand());
			//NavX.reset(new IMU(SPI::Port::kMXP));

			Comp.reset(new frc::Compressor(PCM));

			SmartDashboard::PutBoolean("Two Controllers?", true);

			prefs = frc::Preferences::GetInstance();

			_LEDs.reset(new Talon(LED));
			_LEDs->Set(1.0);

			// This code streams camera 0 to the dashboard using WPILib's CameraServer
			frc::CameraServer::GetInstance()->StartAutomaticCapture(0);

			frc::CameraServer::GetInstance()->AddAxisCamera("10.25.56.6");
		}

		void DisabledInit() override{
			Comp->SetClosedLoopControl(false);
		}

		void DisabledPeriodic() override{
			frc::Scheduler::GetInstance()->Run();
			GlobalPeriodic();
		}

		void AutonomousInit() override{
			/* std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
			 if (autoSelected == "My Auto") {
			 autonomousCommand.reset(new MyAutoCommand());
			 }
			 else {
			 autonomousCommand.reset(new ExampleCommand());
			 }

			AutonomousC.reset(chooser.GetSelected());*/
			Comp->SetClosedLoopControl(true);

			if (AutonomousC.get() != nullptr)
				AutonomousC.reset();
			AutonomousC.reset(new AutonomousMain());

			if (AutonomousC.get() != nullptr){
				AutonomousC->Start();
			}
		}

		void AutonomousPeriodic() override{
			frc::Scheduler::GetInstance()->Run();
			GlobalPeriodic();
		}

		void TeleopInit() override{
			/*if (autonomousCommand != nullptr){
				autonomousCommand->Cancel();
			}*/
			Comp->SetClosedLoopControl(true);
			if(TeleopC.get() != nullptr)
				TeleopC->Start();
		}

		void TeleopPeriodic() override{
			frc::Scheduler::GetInstance()->Run();
			GlobalPeriodic();
		}

		void TestPeriodic() override{
			frc::Scheduler::GetInstance()->Run();
			frc::LiveWindow::GetInstance()->Run();
			GlobalPeriodic();
		}

		void GlobalPeriodic(){
			//CommandBase::drivetrain->_AngleController->SetPID(prefs->GetFloat("kP", 0.0), prefs->GetFloat("kI", 0.0), prefs->GetFloat("kD", 0.0));
			//CommandBase::drivetrain->_AngleController->SetSetpoint(prefs->GetFloat("Setpoint", 0.0));
			//prefs->GetBoolean("Enabled", false) ? CommandBase::drivetrain->_AngleController->Enable() : CommandBase::drivetrain->_AngleController->Disable();

			//SmartDashboard::PutNumber("Error", CommandBase::drivetrain->_AngleController->GetError());
			//SmartDashboard::PutNumber("Setpoint", CommandBase::drivetrain->_AngleController->GetSetpoint());
			//SmartDashboard::PutNumber("Proportional", CommandBase::drivetrain->_AngleController->GetP());
		}
};

START_ROBOT_CLASS(Robot)
