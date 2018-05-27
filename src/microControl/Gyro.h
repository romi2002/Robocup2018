#ifndef __GYRO_H_
#define __GYRO_H_
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
using namespace std;

class Gyro{
private:
	Adafruit_BNO055 bno = Adafruit_BNO055(55);
	int yawOffSet, pitchOffSet, yaw;
	int iTurnCounter = 0, iPitchCounter, lastPitch;
	long lastReadTime = 0, readRateMs = 100;

//Abiel w/h
public:
	Gyro();
	int getYaw();
	int getPitch();
	void resetYaw();
	void resetPitch();
	void resetAll();
	void setYawOffset(int value);
	int getYawOffset();
};
#endif
