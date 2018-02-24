#include "DriveTrain.h"
///Constructor
DriveTrain::DriveTrain() : topRight(1), topLeft(2), lowRight(4), lowLeft(3),enc(19,18), 
							frontSharp(13), backSharp(7), rightSharp(12), leftSharp(14),
								frontRLimitS(0), frontLLimitS(1), backRLimitS(31), backLLimitS(47){
	Serial.println("DriveTrain initializing...");
	Serial.println("DriveTrain initialized");

}

///	MOTORS
void DriveTrain::setRightMotorsVelocity(double velocity){
	topRight.driveVelocity(velocity);
	lowRight.driveVelocity(velocity);
}

void DriveTrain::setLeftMotorsVelocity(double velocity){
	topLeft.driveVelocity(velocity);
	lowLeft.driveVelocity(velocity);
}

void DriveTrain::driveVelocity(double velocity){
	setRightMotorsVelocity(velocity);
	setLeftMotorsVelocity(velocity);
}

void DriveTrain::turn(double rotation){
	setRightMotorsVelocity(rotation * -1);
	setLeftMotorsVelocity(rotation); 
}

/// GYROSCOPE
int DriveTrain::getYaw(){
	return gyro.getYaw();
}
int DriveTrain::getPitch(){
	return gyro.getPitch();
}
void DriveTrain::resetYaw(){
	gyro.resetYaw();
}

void DriveTrain::resetPitch(){
	gyro.resetPitch();
}
void DriveTrain::resetAll(){
	gyro.resetAll();
}

void DriveTrain::turnToAngle(int angle){
	int angleError = shortestAngleTurn(getYaw(), angle);
    double outputMultiplier = mapD(fabs(angleError), 0.0, 30.0, 0.0, 1.0);

	if (outputMultiplier > 1.0) {
		outputMultiplier = 1.0;
	} else if (outputMultiplier < 0.0) {
		outputMultiplier = 0.0;
	}

    while(angleError != 0){
    	angleError = shortestAngleTurn(getYaw(), angle);
		outputMultiplier = mapD(fabs(angleError), 0.0, 30.0, 0.1, 1.0);

		if (outputMultiplier > 1.0) {
			outputMultiplier = 1.0;
		}else if (outputMultiplier < 0.0) {
			outputMultiplier = 0.0;
		}

		if (angleError > 0.0) {
			turn(outputMultiplier);
		} else if (angleError < 0.0) {
			turn(-outputMultiplier);
		}
    }
	turn(0);
}

void DriveTrain::driveStraight(double velocity, int angle){
 	double angleError = shortestAngleTurn(getYaw(), angle);
	double outputMultiplier = mapD(abs(angleError), 0.0, 15.0, 0.0, .8);

	if (outputMultiplier > .8) {
		outputMultiplier = .8;
	} else if (outputMultiplier < 0.0) {
		outputMultiplier = 0.0;
	}
	if (abs(angleError) > 0) {
		if (angleError > 0.0) {
			setLeftMotorsVelocity(velocity);
			setRightMotorsVelocity(velocity - (velocity * outputMultiplier));
		} else if (angleError < 0.0) {
			setLeftMotorsVelocity(velocity - (velocity * outputMultiplier));
			setRightMotorsVelocity(velocity);
		}
	} else {
		setLeftMotorsVelocity(velocity);
		setRightMotorsVelocity(velocity);
	}
}

void DriveTrain::driveDisplacement(double displacement, double velocity){

	double startCount = enc.read();
	double startAngle = getYaw();
	while(enc.read() - startCount < (displacement/wheelCircunference) * encCountsPerRev){
		driveVelocity(velocity);
	}

	driveVelocity(0);
}

int DriveTrain::getDistanceFront(){
	return frontSharp.getDistance();
}

int DriveTrain::getDistanceLeft(){
	return leftSharp.getDistance();
}

int DriveTrain::getDistanceRight(){
	return rightSharp.getDistance();
}

int DriveTrain::getDistanceBack(){
	return backSharp.getDistance();
}


void DriveTrain::alignWithWall(RobotFace faceToAlign){
	Button *right, *left;
	double speed;
	switch(faceToAlign){
		case Back:
			right = &backRLimitS;
			left = &backLLimitS;
			speed = -.75;
		break;

		case Front:
			left = &frontLLimitS;
			right = &frontRLimitS;
			speed = .75;
		break;
	}

	while(!right->getState() || !left->getState()){
		if(!right->getState())
			setRightMotorsVelocity(speed);
		else
			setRightMotorsVelocity(0);
		if(!left->getState())
			setLeftMotorsVelocity(speed);
		else
			setLeftMotorsVelocity(0);
	}
	resetYaw();
	driveVelocity(0);
}