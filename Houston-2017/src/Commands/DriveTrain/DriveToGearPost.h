#ifndef DriveToGearPost_H
#define DriveToGearPost_H

#include "../../CommandBase.h"

class DriveToGearPost: public CommandBase {
public:
	DriveToGearPost();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveToGear_H
