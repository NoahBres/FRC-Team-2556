#ifndef TeleopCommand_H
#define TeleopCommand_H

#include "CommandBase.h"
#include "WPILib.h"
#include "RAR/RARMath.h"

class TeleopCommand:public CommandBase{
	private:
		int _DriveMode; // -1: Left; 0: Front; 1: Right
		bool _SwitchFlag;
		std::shared_ptr<NetworkTable> _Table;
	public:
		TeleopCommand();
		void Initialize();
		void Execute();
		bool IsFinished();
		void End();
		void Interrupted();
		int GetDriveMode();
};

#endif
