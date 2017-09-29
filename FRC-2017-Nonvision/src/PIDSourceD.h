#include "WPILib.h"

class PIDSourceD:public frc::PIDSource{
	private:
		double _Value = 0.0;
	public:
		PIDSourceD(double value = 0.0);
		void SetPIDSourceType(PIDSourceType pidSource);
		double PIDGet();
		void SetValue(double value);
};
