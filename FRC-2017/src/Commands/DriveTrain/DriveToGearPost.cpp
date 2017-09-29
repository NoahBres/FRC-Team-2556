#include <list>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

//#include "CommandBase.h"

//#include "Commands/DriveTrain/DriveToGear.h"
#include <Commands/DriveTrain/DriveToGearPost.h>

extern cs::UsbCamera			g_UsbCamera;
extern cs::CvSink 				g_cvSink;
extern cs::CvSource				g_cvVidOut;

// ============================================================================

DriveToGearPost::DriveToGearPost(float timeout)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(CommandBase::drivetrain.get());
	SetTimeout(timeout);
}

// ----------------------------------------------------------------------------

// Called just before this Command runs the first time
void DriveToGearPost::Initialize() {

}

// ----------------------------------------------------------------------------

// Called repeatedly when this Command is scheduled to run
void DriveToGearPost::Execute() {
	cv::Mat		FrameCam;
	float 		fLeftRigthError;

	// Get a video frame. It may need to be used with more than one process
	g_cvSink.GrabFrame(FrameCam);
	if (!FrameCam.empty())
	{
		// Get the left/right pointing error
		fLeftRigthError = GetTargetError(&FrameCam);
		printf("x %6.3f\n", fLeftRigthError);
#if 0
#ifdef NAVX
		drivetrain.get()->Drive(_xPower, _yPower, (NavX->GetYaw() - _Angle) * -0.05, 0.0);
#else
		fLeftRigthError = fLeftRigthError * 2.0;
		if (fLeftRigthError >  0.5) fLeftRigthError =  0.5;
		if (fLeftRigthError < -0.5) fLeftRigthError = -0.5;
		if (fLeftRigthError != 0.0)
			drivetrain.get()->Drive(0.0, fLeftRigthError, 0.0, 0.0);
#endif
#endif
	} // end if frame not empty
}

// ----------------------------------------------------------------------------

// Make this return true when this Command no longer needs to run execute()
bool DriveToGearPost::IsFinished() {
	if(CommandBase::drivetrain.get()->_XPID->GetError() < 1.0 && CommandBase::drivetrain.get()->_YPID->GetError() < 1.0)
		return false;
	else
		return true;
}

// ----------------------------------------------------------------------------

// Called once after isFinished returns true
void DriveToGearPost::End() {
	CommandBase::drivetrain.get()->Drive(0.0, 0.0, 0.0, 0.0);
}

// ----------------------------------------------------------------------------

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveToGearPost::Interrupted() {

}

// ----------------------------------------------------------------------------

float DriveToGearPost::GetTargetError(cv::Mat * pFrameCam)
	{
#if 1
	int HueLo = 0;
	int HueHi = 255;
	int SatLo = 0;
	int SatHi = 255;
	int ValLo = 170;
	int ValHi = 255;

	cv::Mat 								FrameConverted;
	cv::Mat 								FrameThreshold;
	cv::Mat 								FrameDraw;

	std::vector< std::vector<cv::Point> >	Contours;
	std::vector< std::vector<cv::Point> >	FiltContours;
	struct SuBRect
		{
		cv::Rect		BRect;
		float			fBRAspect;
		float			fContourArea;
		};
	std::list<struct SuBRect>				BoundingRects;
	SuBRect									BoundingRect;
	cv::RNG									rng(12345);

	float									fError;

	fError = 0.0;

//	g_cvSink.GrabFrame(FrameCam);

	// Change image to HSL format
//	cv::cvtColor(*pFrameCam, FrameConverted,  cv::COLOR_BGR2HSV);
	cv::cvtColor(*pFrameCam, FrameConverted,  cv::COLOR_BGR2HLS);

	// Change to B/W based on threshold ranges
//	cv::inRange(FrameConverted, cv::Scalar(HueLo, SatLo, ValLo), cv::Scalar(HueHi, SatHi, ValHi), FrameThreshold);
	cv::inRange(FrameConverted, cv::Scalar(HueLo, ValLo, SatLo), cv::Scalar(HueHi, ValHi, SatHi), FrameThreshold);

	// Find contours
	cv::findContours(FrameThreshold, Contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
//		(InputOutputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method, Point offset=Point())

//	printf("FrameThreshold %d  ", FrameThreshold.cols);

#if 1
	// Filter contours
	for (unsigned int i = 0; i < Contours.size(); i++)
	{
		// Filter based on size
		double dArea = cv::contourArea(Contours[i]);
//				printf(" Area %f ", dArea);
		if (dArea < 100.0)
			continue;

		// Find the upright bounding rectangle
		BoundingRect.BRect        = cv::boundingRect(Contours[i]);
		BoundingRect.fBRAspect    = (float)BoundingRect.BRect.height / (float)BoundingRect.BRect.width;
		BoundingRect.fContourArea = dArea;
//		printf(" R %d %d Aspect %f ", BoundingRect.BRect.height, BoundingRect.BRect.width, BoundingRect.fBRAspect);

		if ((BoundingRect.fBRAspect > 2.0) && (BoundingRect.fBRAspect < 6.0))
		{
			FiltContours.push_back(Contours[i]);
			BoundingRects.push_back(BoundingRect);
		}
	} // end for all contours

	// Sort the bounding rectangles by contour area
//	BoundingRects.sort();

	// Find the centers of the two biggest contours
//		printf("%d", FiltContours.size());
	if (FiltContours.size() == 2)
	{
		// Get the two biggest contours from the front of the list
		cv::Rect	 BRect1, BRect2;
		BRect1 = BoundingRects.front().BRect;
		BoundingRects.pop_front();
		BRect2 = BoundingRects.front().BRect;

		// Calculate where they are on the screen.
		// Note: -1.0 < fError < 1.0
		int x1 = (BRect1.x + BRect1.width)  / 2;
		int x2 = (BRect2.x + BRect1.width)  / 2;
		fError = (x1+x2-160)/160.0;
//		printf("x1 %d x2 %d \n", x1, x2);
	}

	//  Draw contours
	FrameDraw = cv::Mat::zeros(pFrameCam->size(), CV_8UC3);
	for (unsigned int i = 0; i < FiltContours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::drawContours(FrameDraw, FiltContours, i, color, 1, 8, cv::noArray(), 0, cv::Point());
	}
#endif

//#define FRAME	FrameConverted
//#define FRAME	FrameThreshold
#define FRAME	FrameDraw
	if (!FRAME.empty())
		{
		g_cvVidOut.PutFrame(FRAME);
		}
#endif

	return fError;
	} // end GetTargetError()
