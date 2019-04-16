/*
	CoDrone2.cpp	-	CoDrone2	library
	Copyright	(C)	2014 RoboLink.	All	rights reserved.
	LastUpdate : 2018-11-13
*/

#include "CoDrone2.h"
#include "Arduino.h"
#include <EEPROM.h>

//-----------------------------------------------------------------------------//
//-------------------------------- Request ------------------------------------//
//-----------------------------------------------------------------------------//

//--------------------------------- State -------------------------------------//

byte CoDrone2Class::getSystemMode()	//Mode::System::Type
{
	recvGetData(State);
	return modeSystem;
}

byte CoDrone2Class::getFlightMode()	//Mode::Flight::Type
{
	recvGetData(State);
	return modeFlight;
}

byte CoDrone2Class::getFlightControlMode()	//Mode::Control::Flight::Type
{
	recvGetData(State);
	return modeControlFlight;
}

byte CoDrone2Class::getMovementStatus()	//Mode::Movement::Type
{
	recvGetData(State);
	return modeMovement;
}

byte CoDrone2Class::getHeadlessMode()	//Headless::Type
{
	recvGetData(State);
	return headless;
}

byte CoDrone2Class::getControlSpeed()	//controlSpeed::Type
{
	recvGetData(State);
	return controlSpeed;
}

byte CoDrone2Class::getSensorOrientationMode()	//SensorOrientation::Type
{
	recvGetData(State);
	return sensorOrientation;
}

byte CoDrone2Class::getBatteryPercentage()
{
	recvGetData(State);
	return battery;
}

//-------------------------------- Motion -------------------------------------//

acceldata CoDrone2Class::getAccelerometer()	//Acc
{
	recvGetData(Motion);

	acceldata result;
	result.x = imuAccX;
	result.y = imuAccY;
	result.z = imuAccZ;
	return result;
}

gyrodata CoDrone2Class::getAngularSpeed()		//gyro
{
	recvGetData(Motion);

	gyrodata result;
	result.roll = imuGyroRoll;
	result.pitch = imuGyroPitch;
	result.yaw = imuGyroYaw;
	return result;
}

angledata CoDrone2Class::getGyroAngles()	//angle
{
	recvGetData(Motion);

	angledata result;
	result.roll = imuAngleRoll;
	result.pitch = imuAnglePitch;
	result.yaw = imuAngleYaw;
	return result;
}

//-------------------------------- position -----------------------------------//

position CoDrone2Class::getPosition()	//position
{
	recvGetData(Position);

	position result;

	result.x = posX;
	result.y = posY;
	result.z = posZ;
	return result;
}

flightrecord CoDrone2Class::getFlightRecord()
{
	recvGetData(Count);
	
	flightrecord result;

	result.hour = timeHour;
	result.minute = timeMinute;
	result.second = timeSec;
	
	result.takeoff = countTakeOff;
	result.landing = countLanding;
	result.accident = countAccident;
		
	return result;
}

//-----------------------------------------------------------------------------//

rangeData CoDrone2Class::getRange()
{
	recvGetData(Range);
	rangeData result;

	result.left = rangeLeft;
	result.front = rangeFront;
	result.right = rangeRight;
	result.rear = rangeRear;
	result.top = rangetop;
	result.bottom = rangeBottom;

	return result;
}


float CoDrone2Class::getDroneTemp()
{
	recvGetData(Altitude);
	return altitude_temperature;
}

float CoDrone2Class::getPressure()
{
	recvGetData(Altitude);
	return altitude_pressure;
}

float CoDrone2Class::getAltitude()
{
	recvGetData(Altitude);
	return altitude_altitude;
}

float CoDrone2Class::getHeight()
{
	recvGetData(Altitude);
	return altitude_rangeHeight;
}

optdata CoDrone2Class::getOptFlowPosition()
{
	recvGetData(RawFlow);

	optdata result;
	result.x = rawFlowX;
	result.y = rawFlowY;

	return result;
}

rawmotion CoDrone2Class::getRawMotion()
{
	recvGetData(RawMotion);

	rawmotion result;

	result.x = rawImuAccX;
	result.y = rawImuAccY;
	result.z = rawImuAccZ;

	result.roll = rawImuGyroRoll;
	result.pitch = rawImuGyroPitch;
	result.yaw = rawImuGyroYaw;

	return result;
}

trimdata CoDrone2Class::getTrim()
{
	recvGetData(Trim);

	trimdata result;

	result.roll = trimRoll;
	result.pitch = trimPitch;
	result.yaw = trimYaw;
	result.throttle = trimThrottle;

	return result;
}

//-----------------------------------------------------------------------------//

motor CoDrone2Class::getMotor()	//Motor
{
	recvGetData(Motor);

	motor result;

	result.rotationM0 = rotationM0;
	result.valueM0 = valueM0;

	result.rotationM1 = rotationM1;
	result.valueM1 = valueM1;

	result.rotationM2 = rotationM2;
	result.valueM2 = valueM2;

	result.rotationM3 = rotationM3;
	result.valueM3 = valueM3;

	return result;
}

//-----------------------------------------------------------------------------//