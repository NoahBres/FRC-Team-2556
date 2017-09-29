#ifndef DriveToGearPost_H
#define DriveToGearPost_H

#include <opencv2/core.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/imgproc.hpp>

#include "../../CommandBase.h"

class DriveToGearPost: public CommandBase {
public:
	DriveToGearPost(float timeout);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	float GetTargetError(cv::Mat * pFrameCam);

};

#endif  // DriveToGear_H
