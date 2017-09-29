#ifndef DriveFromPlayerStation_H
#define DriveFromPlayerStation_H

#include "CommandBase.h"

class DriveFromPlayerStation : public CommandBase {
private:
	float _PlayerStations [3] = {-3, 0, 3};
	float _Gears [3] = {-1.5, 0, 1.5};
public:
	DriveFromPlayerStation(int playerStation, int gear);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	int PS;
	int gearPos;
};

#endif  // DriveFromPlayerStation_H
