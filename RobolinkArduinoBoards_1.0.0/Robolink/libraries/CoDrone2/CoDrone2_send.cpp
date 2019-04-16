/*
	CoDrone2.cpp	-	CoDrone2	library
	Copyright	(C)	2014 RoboLink.	All	rights reserved.
	LastUpdate : 2018-11-13
*/

#include "CoDrone2.h"
#include "Arduino.h"
#include <EEPROM.h>

//-----------------------------------------------------------------------------------------------------------//
//--------------------------------------------- flight event ------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

void CoDrone2Class::flightEvent(byte _event)
{
	sendProcess(Command, 2, 0x07 | (_event<<8)); //command, length, _event
}

void CoDrone2Class::takeoff()
{
	flightEvent(TakeOff);
}

void CoDrone2Class::land()
{
	flightEvent(Landing);
}

void CoDrone2Class::emergencyStop()
{
	flightEvent(Stop);
}

void CoDrone2Class::returnHome()
{
 	flightEvent(Return);

 	/*
 	delay(50);

 	byte mode = CoDrone2.getMovementStatus();      // 드론의 이동 상태 값을 가져옵니다.

	 CoDrone2.setLED(Gold, BodyHold, 100);
	 delay(50);

	while(mode == 0x02)	//Hovering
	{
		mode = CoDrone2.getMovementStatus();          // 드론의 이동 상태 값을 가져옵니다.
		hover(0.5);
	}
	 delay(50);
  CoDrone2.setLED(Blue, BodyHold, 100);
  */
}

//-----------------------------------------------------------------------------------------------------------//
//---------------------------------------- ControlFlightMode ------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

//Attitude    = 0x10, // 자세 - X,Y는 각도(deg)로 입력받음, Z,Yaw는 속도(m/s)로 입력 받음
//Position    = 0x11, // 위치 - X,Y,Z,Yaw는 속도(m/s)로 입력 받음
//Function    = 0x12, // 기능 - X,Y,Z,Yaw는 속도(m/s)로 입력 받음

void CoDrone2Class::setControlFlightMode(byte _event)
{
	if(_event == Attitude) _event = 0x10;
	else if (_event == Position) _event = 0x11;

	sendProcess(Command, 2, 0x02 | (_event<<8)); //command, length, _event
}

//-----------------------------------------------------------------------------------------------------------//
//---------------------------------------- HeadlessType ------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

// 1 Headless,   // 사용자 중심 좌표	Headless ON
// 2 Normal,     // 드론 중심 좌표		Headless OFF

void CoDrone2Class::setHeadlessType(byte _event)
{
	sendProcess(Command, 2, 0x03 | (_event<<8)); //command, length, _event
}

//-----------------------------------------------------------------------------------------------------------//
//---------------------------------------- controlSpeed ------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

//제어 속도(1, 2, 3)

void CoDrone2Class::setControlSpeed(byte _event)
{
	sendProcess(Command, 2, 0x04 | (_event<<8)); //command, length, _event
}



//-----------------------------------------------------------------------------------------------------------//
//--------------------------------------- Command With LED Control ------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

/*
void CoDrone2Class::setEventLEDCommand(byte color, byte sendMode, int sendInterval, byte repeat)	//color
{
	// take off 0x11;
//	sendProcess(Command, 2, 0x07 | (_event<<8)); //command, length, _event
//	sendProcess(LightEvent, 5, sendMode | (sendInterval<<8), (sendInterval >>8) | (repeat<<8), color);

	sendProcess(Command, 2, 0x07 | (0x11<<8)); //command, length, _event
	
	
}
*/


//-----------------------------------------------------------------------------------------------------------//
//----------------------------------------- LED Control -----------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

//------------------------------------------- setLED --------------------------------------------------------//

void CoDrone2Class::setLED(byte color, byte sendMode, int sendInterval)	//color
{
	sendProcess(LightMode, 4, sendMode | (sendInterval<<8), (sendInterval >>8) | (color<<8));
}

void CoDrone2Class::setLED(byte r, byte g, byte b, byte sendMode, int sendInterval)	//r, g, b
{
	sendProcess(LightMode, 6, sendMode | (sendInterval<<8), (sendInterval >>8) | (r<<8), g | (b<<8));
}

//----------------------------------------- setDefaultLED ---------------------------------------------------//

void CoDrone2Class::setDefaultLED(byte color, byte sendMode, int sendInterval)	//color
{
	sendProcess(LightDefault, 4, sendMode | (sendInterval<<8), (sendInterval >>8) | (color<<8));
}

void CoDrone2Class::setDefaultLED(byte r, byte g, byte b, byte sendMode, int sendInterval)	//r, g, b
{
	sendProcess(LightDefault, 6, sendMode | (sendInterval<<8), (sendInterval >>8) | (r<<8), g | (b<<8));
}

//------------------------------------------- setEventLED ---------------------------------------------------//

void CoDrone2Class::setEventLED(byte color, byte sendMode, int sendInterval, byte repeat)	//color
{
	sendProcess(LightEvent, 5, sendMode | (sendInterval<<8), (sendInterval >>8) | (repeat<<8), color);
}

void CoDrone2Class::setEventLED(byte r, byte g, byte b, byte sendMode, int sendInterval, byte repeat)	//r, g, b
{
	sendProcess(LightEvent, 7, sendMode | (sendInterval<<8), (sendInterval >>8) | (repeat<<8), r | (g<<8), b);
}

//-----------------------------------------------------------------------------------------------------------//
//--------------------------------------------- utility -----------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

void CoDrone2Class::moveMotor(byte rotation, int rpm)
{
		sendProcess(Motor, 3, rotation | (rpm<<8), rpm >>8);
}

void CoDrone2Class::movemotorSingle(byte taget, byte rotation, int rpm)
{
		sendProcess(MotorSingle, 4, taget | (rotation<<8), rpm);
}

void CoDrone2Class::clearBias()
{
	sendProcess(Command, 1, 0x05); //command, length, ClearBias
}

void CoDrone2Class::clearTrim()
{
	sendProcess(Command, 1, 0x06); //command, length, ClearTrim
}

void CoDrone2Class::setWeight(float weight)
{
	sendProcess(Weight, 4, weight); //command, length, ClearTrim
}

void CoDrone2Class::lostConnectionSet(uint16_t timeNeutral, uint16_t timeLanding, uint32_t timeStop)	//0 ~ 65,535, 0 ~ 65,535, 0 ~ 4,294,967,295
{
	sendProcess(LostConnection, 8, timeNeutral, timeLanding, timeStop); //command, length, ClearTrim
}

void CoDrone2Class::pingCheck()
{
	sendProcess(Ping, 0); //command, length
}
//-----------------------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------------------//
//------------------------------------------- Movement ------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------//
//------------------------------------------- Position ------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

void CoDrone2Class::controlPosition(float posX, float posY, float posZ, float vel, int heading, int velR)
{
	sendProcess(Control, 20, posX, posY, posZ, vel, heading, velR); //command, length, ClearTrim
}

//-----------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------//
//--------------------------------------------- goPositon --------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

//((Dir1, meter1), (Dir2, meter2), (Dir3, meter3), Time1), (Turn, angle, Time2)	10
void CoDrone2Class::goPositon(int direction1, float pos1, int direction2, float pos2, int direction3, float pos3, float time1, int direction4, float pos4, float time2)
{
	goPositonProcess(direction1, pos1, direction2, pos2, direction3, pos3, time1, direction4, pos4, time2);
}

//((Dir1, meter1), (Dir2, meter2), Time1), (Turn, angle, Time2)	8
void CoDrone2Class::goPositon(int direction1, float pos1, int direction2, float pos2, float time1, int direction4, float pos4, float time2)
{
	goPositonProcess(direction1, pos1, direction2, pos2, 0, 0, time1, direction4, pos4, time2);
}

//((Dir1, meter1), Time1), (Turn, angle, Time2)		6
void CoDrone2Class::goPositon(int direction1, float pos1, float time1, int direction4, float pos4, float time2)
{
	goPositonProcess(direction1, pos1, 0, 0, 0, 0, time1, direction4, pos4, time2);
}

//((Dir1, meter1), (Dir2, meter2), (Dir3, meter3), Time1)	7
void CoDrone2Class::goPositon(int direction1, float pos1, int direction2, float pos2, int direction3, float pos3, float time1)
{
	goPositonProcess(direction1, pos1, direction2, pos2, direction3, pos3, time1, 0, 0, 0);
}

//((Dir1, meter1), (Dir2, meter2), Time1)	5
void CoDrone2Class::goPositon(int direction1, float pos1, int direction2, float pos2, float time1)
{
	goPositonProcess(direction1, pos1, direction2, pos2, 0, 0, time1, 0, 0, 0);
}

//((Dir1, meter1), Time1)		3
void CoDrone2Class::goPositon(int direction1, float pos1, float time1)
{
	if ((direction1 == direction_left_turn) || (direction1 == direction_right_turn))
	{
		goPositonProcess(0, 0, 0, 0, 0, 0, 0, direction1, pos1, time1);
	}
	else
	{
		goPositonProcess(direction1, pos1, 0, 0, 0, 0, time1, 0, 0, 0);
	}
}

/*
//(Dir1, meter1)
void CoDrone2Class::goPositon(int direction1, float pos1)
{
	if ((direction1 == direction_left_turn) || (direction1 == direction_right_turn))
	{
		goPositonProcess(0, 0, 0, 0, 0, 0, 0, direction1, pos1, 5);
	}
	else
	{
		goPositonProcess(direction1, pos1, 0, 0, 0, 0, 5, 0, 0, 0);
	}
}
*/


void CoDrone2Class::goPositonProcess(int direction1, float pos1, int direction2, float pos2, int direction3, float pos3, float time1, int direction4, float pos4, float time2)
{
	float x = 0, y = 0, z = 0, t = 0, v = 0, rv = 0;

	int 	_dir[4] = {direction1, direction2, direction3, direction4};
	float _pos[4] = {pos1, pos2, pos3, pos4};
	
	//---------------------------------------------------------//
	for(int i = 0; i < 3; i++)
	{
		if(_pos[i] < 0) _pos[i] = _pos[i] * -1;
		else	if(_pos[i] > 10) _pos[i] = 10;
	}

	if(pos4 < 0) 	pos4 = pos4 * -1;
	if(pos4 > 360)			 _pos[3] = 360;
	else if(pos4 < -360) _pos[3] = -360;

//---------------------------------------------------------//

	if(time1 > 0)
	{
		for(int i = 0; i < 3; i++)
		{
			float _v = _pos[i] / time1;
			if(_v > v) v = _v;
		}
		if(v > 5) v = 5;
	}

	if(time2 > 0)	rv = pos4 / time2;
	if (rv < 10) rv = 10;
	else if (rv > 180) rv = 180;

//---------------------------------------------------------//

	for(int i = 0; i < 4; i++)
	{		
		if(_dir[i] == direction_forward)					x =  _pos[i];
		else if(_dir[i] == direction_backward)		x = -_pos[i];
		else if(_dir[i] == direction_left)				y =  _pos[i];
		else if(_dir[i] == direction_right)				y = -_pos[i];
		else if(_dir[i] == direction_up)					z =  _pos[i];		
		else if(_dir[i] == direction_down)				z = -_pos[i];						
		else if(_dir[i] == direction_left_turn)		t =  _pos[i];
		else if(_dir[i] == direction_right_turn)	t = -_pos[i];						
	}

//-----------------------------------------------------//
	controlPosition(x, y, z, v, t, rv);
//-----------------------------------------------------//

	float _delayTime = (time1 > time2 ? time1 : time2);
	delay(_delayTime * 1000);

/*
		Serial.print(x);	Serial.print("\t");
		Serial.print(y);	Serial.print("\t");
		Serial.print(z);	Serial.print("\t");
		Serial.print(v);	Serial.print("\t");
		Serial.print(t);	Serial.print("\t");
		Serial.print(rv);	Serial.print("\t");
		Serial.print(_delayTime);	Serial.println("\t");
*/

//-----------------------------------------------------//
//	move(0,0,0,0);
//-----------------------------------------------------//
//	delay(1000);
//-----------------------------------------------------//

}

//-----------------------------------------------------------------------------------------------------------//
//------------------------------------------ goToHeight -----------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//


void CoDrone2Class::goToHeightMove(float _range) // 0 ~2
{
	int _dir = 0;
	//---------------------------------------------------------------//
	float _height = getHeight();
	//---------------------------------------------------------------//

	if (_height < _range)			 _dir = 1;	// up
	else if(_height > _range)			_dir = -1;	// down

	while(1)
	{
		_height = getHeight();

	//	if (_height < _range)			 _dir = 1;	// up
	//	else if(_height > _range)			_dir = -1;	// down

		if (receive_Altitude_Success)
		{
			if((_dir > 0) && (_height < _range))	//up
			{
				move(0,0,0, 70);
				delay(30);
			}
			else if((_dir < 0) && (_height > _range))	//down
			{
				move(0,0,0, -50);
				delay(30);
			}
			else
			{
				move(0,0,0,0);
				delay(50);
				break;
			}
		}
	}
}
void CoDrone2Class::goToHeightPosition(float _range) // 0 ~2
{
			int _dir = 0;
	//---------------------------------------------------------------//
	float _height = getHeight();
	//---------------------------------------------------------------//

	if (_height < _range)			 _dir = 1;	// up
	else if(_height > _range)			_dir = -1;	// down


	//direction = (direction == LEFT ? 1 : -1);
	//degree = direction * degree;

	//float speed = degree / time;

	//controlPosition(0, 0, 0, 0, degree, speed);

//	hover(time);

	/*
	while(1)
	{
		_height = getHeight();

		if (receive_Altitude_Success)
		{
			if((_dir > 0) && (_height < _range))
			{
				move(0,0,0, 70);
			}
			else if((_dir < 0) && (_height > _range))
			{
				move(0,0,0, -30);
			}
			else
			{
				move(0,0,0,0);
				break;
			}
		}
	}
	*/
}



void CoDrone2Class::goToHeight(float _range) // 0 ~2
{
	int _dir = 0;
	//---------------------------------------------------------------//
	float _height = getHeight();
	//---------------------------------------------------------------//

	if (_height < _range)			 _dir = 1;	// up
	else if(_height > _range)			_dir = -1;	// down

	while(1)
	{
		_height = getHeight();

		if (receive_Altitude_Success)
		{
			if((_dir > 0) && (_height < _range))	//up
			{
				move(0,0,0, 70);
				delay(30);
			}
			else if((_dir < 0) && (_height > _range))	//down
			{
				move(0,0,0, -50);
				delay(30);
			}
			else
			{
				move(0,0,0,0);
				delay(50);
				break;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------//

void CoDrone2Class::rotate180()
{
	turnDegree(LEFT,180,3);
}

//-------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------//
//------------------------------------------- turn ----------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//
/*
 void CoDrone2Class::turn(int direction)
{
	int y = 0;
	if (direction == direction_right)		y = -30;
	else if (direction_left)						y = 30;

	move(0,0,y,0);
	unsigned long startMillis = millis();
	while(millis() - startMillis < 1000)
	{
		move(0,0,y,0);
		delay(100);
	}
	hover(1);
}

 void CoDrone2Class::turn(int direction, float duration)
{
	int y = 0;
	if (direction == direction_right)	y = -30;
	else if (direction_left)					y = 30;

	move(0,0,y,0);
	unsigned long startMillis = millis();
	while(millis() - startMillis < duration*1000)
	{
		move(0,0,y,0);
		delay(50);
	}
	hover(1);
}
*/
void CoDrone2Class::turn(int direction, int power, float duration)
{
	int y = power ;
	if(direction == direction_right)			y *= -1;

	move(0,0,y,0);
	unsigned long startMillis = millis();
	while(millis() - startMillis < duration*1000)
	{
		move(0,0,y,0);
		delay(25);
	}
	//if(duration != 0)
	hover(1);
}

//-----------------------------------------------------------------------------------------------------------//
//------------------------------------------ turnDegree -----------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

/*
 void CoDrone2Class::turnDegree(int direction, int degree)
{
	direction = (direction == LEFT ? 1 : -1);
	degree = direction * degree;

	float speed = 10;
	float time = degree / speed;

	controlPosition(0, 0, 0, 0, degree, 10);

	hover(time);
//	delay(time * 1000);
}
*/

/*
 void CoDrone2Class::turnDegree(int direction, int degree, float time)
{
	direction = (direction == LEFT ? 1 : -1);
	degree = direction * degree;

	float speed = degree / time;

	controlPosition(0, 0, 0, 0, degree, speed);

	hover(time);
	//delay(time * 1000);
}
*/


void CoDrone2Class::turnDegree(int direction, int degree, float time)
{
	/*
	int _bias = 3;
	int _dir = 0;
	int _pow = 20;

	if (_angle > 0)	_dir =  1;
	else          	_dir = -1;

	gyrodata angle;
	angle = CoDrone.getGyroAngles();
	int yawPast = angle.yaw;

	_angle = _dir * (abs(_angle) - _bias) + yawPast;

	while (1)
	{
		angle = CoDrone.getGyroAngles();
		int _nowAngle = angle.yaw;

		if (abs(yawPast - _nowAngle) > 180)	_angle -= _dir * 360;

		yawPast = _nowAngle;
		YAW = _dir * _pow;

		if ((_dir > 0) && (_angle > _nowAngle)) 			CoDrone.Control();	// right turn
		else if ((_dir < 0) && (_angle < _nowAngle)) 	CoDrone.Control();	// left turn
		else
		{
			YAW = 0;
			CoDrone.Control();
			break;
		}
	}
	*/

	direction = (direction == LEFT ? 1 : -1);
	degree = direction * degree;

	float speed = degree / time;

	controlPosition(0, 0, 0, 0, degree, speed);

	//hover(time);
	delay(time * 1000);
}



//-----------------------------------------------------------------------------------------------------------//
//----------------------------------------------- go --------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//
/*
 void CoDrone2Class::go(int direction)
{
	int r,p,t;
	r = 0;
	p = 0;
	t = 0;

	switch(direction)
	{
		case direction_forward:
			p = 20;
			break;
		case direction_up:
			t = 20;
			break;
		case direction_right:
			r = 20;
			break;

		case direction_backward:
			p = -20;
			break;
		case direction_down:
			t = -20;
			break;
		case direction_left:
			r = -20;
			break;
	}
	move(r,p,0,t);
	unsigned long startMillis = millis();
	while(millis() - startMillis < 1000)
	{
		move(r,p,0,t);
		delay(50);
	}
	hover(1);
}

 void CoDrone2Class::go(int direction, float duration)
{
	int r,p,t;
	r = 0;
	p = 0;
	t = 0;

	switch(direction)
	{
		case direction_forward:
			p = 20;
			break;
		case direction_up:
			t = 20;
			break;
		case direction_right:
			r = 20;
			break;
		case direction_backward:
			p = -20;
			break;
		case direction_down:
			t = -20;
			break;
		case direction_left:
			r = -20;
			break;
	}
	move(r,p,0,t);
	unsigned long startMillis = millis();
	while(millis() - startMillis < duration*1000)
	{
		move(r,p,0,t);
		delay(50);
	}
	if(duration != 0)
		hover(1);
}
*/
void CoDrone2Class::go(int direction, int power, float duration)
{
	int r,p,t;
	r = 0;
	p = 0;
	t = 0;

	switch(direction)
	{
		case direction_forward:
			p = power;
			break;
		case direction_up:
			t = power;
			break;
		case direction_right:
			r = power;
			break;
		case direction_backward:
			p = (-1)*power;
			break;
		case direction_down:
			t = (-1)*power;
			break;
		case direction_left:
			r = (-1)*power;
			break;
	}
	unsigned long startMillis = millis();
	while(millis() - startMillis < duration*1000)
	{
		move(r,p,0,t);
		delay(50);
	}
	if(duration != 0)
		hover(1);
}

void CoDrone2Class::hover(float duration)
{
	move(0,0,0,0);
	delay(50);
	unsigned long startMillis = millis();
	while(millis() - startMillis < duration * 1000)
	{
		move(0,0,0,0);
		delay(50);
		//delay(30);
	}
}

//-----------------------------------------------------------------------------------------------------------//
//------------------------------------------------ move -----------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

/*
 void CoDrone2Class::move()
{
	sendProcess(Control, 4, moveRoll | (movePitch << 8), moveYaw | (moveThrottle << 8) ); //command, length
}

 void CoDrone2Class::move(float duration)
{
	unsigned long startMillis = millis();
	while(millis() - startMillis < duration*1000)
	{
		move();
		//gap for command sending
		delay(50);
	}
	hover(1);
}
*/
void CoDrone2Class::move(int _roll, int _pitch, int _yaw, int _throttle)
{
	sendProcess(Control, 4, _roll | (_pitch << 8), _yaw | (_throttle << 8) ); //command, length
}

void CoDrone2Class::move(int _roll, int _pitch, int _yaw, int _throttle, float duration)
{
	unsigned long startMillis = millis();
	while(millis() - startMillis < duration*1000)
	{
		move(_roll, _pitch, _yaw, _throttle);
		delay(50);
	}
	hover(1);
}


/*
 void CoDrone2Class::setRoll(int _roll)
{
	moveRoll = _roll;
}
 int CoDrone2Class::getRoll()
{
	return moveRoll;
}
 void CoDrone2Class::setPitch(int _pitch)
{
	movePitch = _pitch;
}
 int CoDrone2Class::getPitch()
{
	return movePitch;
}
 void CoDrone2Class::setYaw(int _yaw)
{
	moveYaw = _yaw;
}
 int CoDrone2Class::getYaw()
{
	return moveYaw;
}
 void CoDrone2Class::setThrottle(int _throttle)
{
	moveThrottle = _throttle;
}
 int CoDrone2Class::getThrottle()
{
	return moveThrottle;
}
*/
//-----------------------------------------------------------------------------------------------------------//