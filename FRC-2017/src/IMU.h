/*
 * IMU.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Andrew Parmer
 */

#ifndef IMU_H
#define IMU_H

#include <AHRS.h>
#include <thread>
#include <mutex>
#include <cmath>
#include <math.h>

#include <RobotMap.h>

class IMU:public AHRS{
	private:
		int _Yaw;
	public:
		IMU(SPI::Port Port);
		int GetAdjustedYaw();
		void Update();
};

#ifdef NAVX
extern std::unique_ptr<IMU> NavX;
#endif

#endif
