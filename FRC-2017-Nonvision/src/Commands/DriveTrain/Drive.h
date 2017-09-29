#ifndef Drive_H
#define Drive_H

#include "CommandBase.h"

class Drive : public CommandBase {
private:
	float _xPower, _yPower, _Rotation;
public:
	Drive(float timeout, float xPower, float yPower, float rotation);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Drive_H
