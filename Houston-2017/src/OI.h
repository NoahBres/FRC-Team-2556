#ifndef OI_H
#define OI_H

#include <WPILib.h>

class OI{
	public:
		std::unique_ptr<frc::XboxController> Xbox1;
		std::unique_ptr<frc::XboxController> Xbox2;
		OI();
};

#endif  // OI_H
