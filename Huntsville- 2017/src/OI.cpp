#include "OI.h"

OI::OI(){
	Xbox1.reset(new frc::XboxController(0));
	Xbox2.reset(new frc::XboxController(1));
}
