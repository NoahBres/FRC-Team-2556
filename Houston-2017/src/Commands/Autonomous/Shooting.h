#ifndef Shooting_H
#define Shooting_H

#include "CommandBase.h"

class Shooting : public CommandBase {
private:
	float _ShooterPower = 0.0;
	float _TankPower = 0.0;
public:
	Shooting(float timeout, float shooterPower, float tankPower);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Shooting_H
