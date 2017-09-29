/*
 * IMU.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: Andrew Parmer
 */

#include "IMU.h"

IMU::IMU(frc::SPI::Port Port):
	AHRS(Port),
	_Yaw(0){

}

int IMU::GetAdjustedYaw(){
	return _Yaw;
}

void IMU::Update(){
	_Yaw = GetYaw();
}
