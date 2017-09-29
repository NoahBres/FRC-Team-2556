#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
//#include "CommandBase.h"
#include "RobotMap.h"

#include "Commands/Autonomous/AutonomousMain.h"
#include "Commands/Teleoperated/TeleopCommand.h"

#include "IMU.h"

#ifdef NAVX
std::unique_ptr<IMU>		NavX;
#endif

cs::UsbCamera 				g_UsbCamera;
cs::CvSink 					g_cvSink;
cs::CvSource				g_cvVidOut;

class Robot:public frc::IterativeRobot{
	private:
		// Command processors
		std::unique_ptr<frc::Command>	AutonomousC;
		std::unique_ptr<TeleopCommand>	TeleopC;

		// Other WPIlib objects
		std::unique_ptr<frc::Compressor> Comp;
		std::shared_ptr<NetworkTable>	Table;

		// Stored preferences object
		frc::Preferences *prefs;
		float			  fAutoMode;

		std::unique_ptr<Talon> _LEDs;
		//frc::SendableChooser<frc::Command*> chooser;

	public:
		void RobotInit() override{
			CommandBase::init();

			// Put some info on the LabVIEW dashboard
			std::string  sBuildDate = std::string(__DATE__) + " " + std::string(__TIME__);
			SmartDashboard::PutString("DB/String 0", "FRC 2017");
			SmartDashboard::PutString("DB/String 5", sBuildDate.c_str());
			SmartDashboard::PutString("DB/String 6", "                    ");

			/*chooser.AddDefault("Default Auto", new ExampleCommand());
			chooser.AddObject("My Auto", new MyAutoCommand());
			frc::SmartDashboard::PutData("Auto Modes", &chooser);*/

			TeleopC.reset(new TeleopCommand());
#ifdef NAVX
			NavX.reset(new IMU(SPI::Port::kMXP));
#endif
			Comp.reset(new frc::Compressor(PCM));

			SmartDashboard::PutBoolean("Two Controllers?", true);

			// Retrieve saved preferences and write them to the driver station
			prefs = frc::Preferences::GetInstance();
			fAutoMode = prefs->GetFloat("PREF_AUTOMODE", 0.0);
//			SmartDashboard::PutNumber("DB/Slider 0", fAutoMode);

			_LEDs.reset(new Talon(LED));
			_LEDs->Set(-0.1);

			// This code streams camera 0 to the dashboard using WPILib's CameraServer
			g_UsbCamera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
			g_UsbCamera.SetResolution(320,240);
			g_UsbCamera.SetFPS(15);

			// Connect up the camera source and sinks for vision processing
			g_cvSink   = CameraServer::GetInstance()->GetVideo();
			g_cvVidOut = CameraServer::GetInstance()->PutVideo("Processed", 320, 240);
			g_cvVidOut.SetResolution(320,240);

			// Make the IP camera known to the dashboard for easy selection
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
			// Save the autonomous mode value to the preferences
			prefs->PutFloat("PREF_AUTOMODE", fAutoMode);

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
			frc::LiveWindow::GetInstance()->Run();
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
#ifdef NAVX
			SmartDashboard::PutNumber("Angle", NavX->GetAngle());
#endif

			//CommandBase::drivetrain.get()->Set

			//CommandBase::drivetrain->_AngleController->SetPID(prefs->GetFloat("kP", 0.0), prefs->GetFloat("kI", 0.0), prefs->GetFloat("kD", 0.0));
			//CommandBase::drivetrain->_AngleController->SetSetpoint(prefs->GetFloat("Setpoint", 0.0));
			//prefs->GetBoolean("Enabled", false) ? CommandBase::drivetrain->_AngleController->Enable() : CommandBase::drivetrain->_AngleController->Disable();

			//SmartDashboard::PutNumber("Error", CommandBase::drivetrain->_AngleController->GetError());
			//SmartDashboard::PutNumber("Setpoint", CommandBase::drivetrain->_AngleController->GetSetpoint());
			//SmartDashboard::PutNumber("Proportional", CommandBase::drivetrain->_AngleController->GetP());
		}
};

START_ROBOT_CLASS(Robot)
