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

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>


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
			_LEDs->Set(-0.1);

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
// Declares Usb Camera
#ifdef CAMERA_SERVER
		cs::UsbCamera	UsbCamera;
#endif
//
#if defined(CAMERA) || defined(IMG_PROCESS)
		cs::UsbCamera		UsbCamera1;
		cs::UsbCamera		UsbCamera2;
		cs::UsbCamera		UsbCamera3;
		cs::CvSink			cvSink1;
		cs::CvSink			cvSink2;
		cs::CvSink 			cvSink3;
		cs::CvSource		cvVidOut;
#endif

#ifdef IMG_PROCESS
	int					HueLo, HueHi;
	int					SatLo,SatHi;
	int					ValLo, ValHi;
#endif

#if defined(CAMERA) || defined(IMG_PROCESS)
	UsbCamera1 = CameraServer::GetInstance()->StartAutomaticCapture();
	UsbCamera1.SetResolution(160, 120);
	UsbCamera1.SetFPS(5)

	UsbCamera2 = CameraServer::GetInstance()->StartAutomaticCapture();
	UsbCamera2.SetResolution(160, 120);
	UsbCamera2.SetFPS(5)
#endif

#ifdef IMG_PROCESS
#endif

#if defined(CAMERA) && !defined(IMG_PROC)
	cv::Mat 			FrameCam;
#endif

#ifdef IMG_PROCESS
		HueLo = 0;
		HueHi = 255;
		SatLo = 0;
		ValLo = 250;
		ValHi = 255;

		cv::Mat 		FrameCam;
		cv::Mat 		FrameHsv;
		cv::Mat 		FrameThreshold;
		cv::Mat			FrameEdges;
		cv::Mat 		FrameDraw;

		std::vector< std::vector<cv::Point> > Contours;
		std::vector< std::vector<cv::point> > FiltContours;
		std::vector< cv::Rect>				  BoundingRects;
		cv::RNG

		cvSink1.GrabFrame(FrameCam);

		cv::cvtColor(FrameCam, FrameHsv, cv::COLOR_BGR2HSV);

		cv::inRange(FrameHsv, cv::Scalar(HueLo, SatLo, ValLo), cv::Scalar(HueHi, SatHi, ValHi), FrameThreshold);

		cv::Canny(FrameThreshold, FrameEdges, 100, 200, 3);

		cv::findContours(FrameThreshold, Contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));

#if 1
		for (unsined int i = 0; < Contours.size(); i++)
		{

			double dArea = cv::contourArea(Contours[i]);

			if (dArea < 100.0)
				continue;
			cv::Rect BRect = cv::boundRect(Contours[i]);
			float fBRAspect = (float)BRect.height / (float) BRect.width;

#if 1
			if ((fBRAspect > 2.0) && (fBRAspect < 6.0))
			{

				FiltContours.push_back(Contours[i]);
				BoundRects.push_back(BRect);
			}

#else
			BoundRects.push_back(BRect);
			FiltContours.push_back(Contours[i]);
#endif
	}

#if 0
	// Find the centers of the two best rectangles
	printf("%d", FiltContours.size());
			if (FiltContours.size() == 2)
				{
					int x1 = (BoundingRects[0].x + BoundingRects[0].width)  / 2;
					int y1 = (BoundingRects[0].y - BoundingRects[0].height) / 2;
					int x2 = (BoundingRects[1].x + BoundingRects[1].width)  / 2;
					int y2 = (BoundingRects[1].y - BoundingRects[1].height) / 2;
					printf(" - x1 %d y1 %d  x2 %d y2 %d", x1, y1, x2, y2);
				}
	printf("\n");

#endif

	/// Draw contours
		FrameDraw = cv::Mat::zeros(FrameCam.size(), CV_8UC3);
		for (unsigned int i = 0; i < FiltContours.size(); i++)
				{
					cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
					cv::drawContours(FrameDraw, FiltContours, i, color, 1, 8, cv::noArray(), 0, cv::Point());
				}
#endif


	//#define FRAME	FrameHsv
	//#define FRAME	FrameThreshold
	//#define FRAME	FrameEdges
#define FRAME	FrameDraw
		if (!FRAME.empty())
				{
					cvVidOut.PutFrame(FRAME);
				}

#else
	//	CameraServer::GetInstance()->SetImage(psuFrame);
#endif

#ifdef GYRO_ADXRS450
		SmartDashboard::PutNumber("Gyro Angle", pclGyroAdxrs450->GetAngle());
#endif

#ifdef IMG_PROCESS
		// Stop image acquisition
#endif


};

START_ROBOT_CLASS(Robot)
