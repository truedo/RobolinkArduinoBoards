/*
	CoDrone2.cpp	-	CoDrone2	library
	Copyright	(C)	2014 RoboLink.	All	rights reserved.
	LastUpdate : 2018-11-13
*/

#include "CoDrone2.h"
#include "Arduino.h"
#include <EEPROM.h>

CoDrone2Class CoDrone2;

//-----------------------------------------------------------------------------------------------------------//
//--------------------------------------------- begin -------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

	void CoDrone2Class::begin()
	{
		CodeLoader2Init(0);
	}
	void CoDrone2Class::begin(float time)
	{
		CodeLoader2Init(time);
	}

//-----------------------------------------------------------------------------------------------------------//
//-------------------------------------------- receive ------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

void CoDrone2Class::receive()
{
	while (DRONE_SERIAL.available() > 0)
	{
	  //------------------------------------------------------------------------------//
	  //------------------------------------------------------------------------------//
	 	int input = DRONE_SERIAL.read();

	  recvBuff[recvIndex++] = (char)input;

	  if (recvIndex >= MAX_PACKET_LENGTH)
	  {
	    checkHeader = 0;
	    recvIndex = 0;
	  }

	  else
	  {
	  	
	   if(checkHeader == 0)
	    {
	      if (recvBuff[recvIndex-1] == START1)	 checkHeader = 1;	     
	    }

	    else if (checkHeader == 1)
	    {
	      if (recvBuff[recvIndex-1] == START2)
	      {
	      	checkHeader = 2;
	      	recvIndex = 0;
	      }
	    }    
	    	    
	    //------------------------------------------------------------------------------//
	    //------------------------------------------------------------------------------//

	    else if (checkHeader == 2)
	    {
	      if (recvIndex > 4)
	      {
	      	recvLength = recvBuff[1]; // Receive Length			    

	        if (recvLength > 0 && recvLength + 6 == recvIndex)
	        {
	        	recvDtype = recvBuff[0];  // Receive Dtype
	          byte crcBuff[2];

	          crcBuff[0] = recvBuff[recvIndex - 2];
	          crcBuff[1] = recvBuff[recvIndex - 1];

	          if (CRC16_Check(recvBuff, recvLength + 2, crcBuff)) recvEventCheck(recvBuff);

	          checkHeader = 0;
	          recvIndex = 0;
	        }
	      }
	    }

	    else
	    {
	      checkHeader = 0;
	      recvIndex = 0;
	    }
	  }
	}
}


//-----------------------------------------------------------------------------------------------------------//
//--------------------------------------- receive Event Check -----------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

void CoDrone2Class::recvEventCheck(byte _completeData[])
{
	int _indexOffset = 4;
	
  if (recvDtype == Ack)  //Ack
  {
  	receive_Ack_Success = true;
  	ackDataType	=	_completeData[8+_indexOffset];

  	/*
	  #if	defined(DEBUG_MODE_ENABLE)
	  if(debugLevel > 1)
		{
		    DEBUG_SERIAL.println();
		    DEBUG_SERIAL.println(F("- Ack"));
		    DEBUG_SERIAL.print(F("dataType\t"));
		    DEBUG_SERIAL.println(ackDataType);
	  }
	  #endif
	  */
  }

  else if (recvDtype == Ping)  //Ping
  {
  	/*
  	 #if	defined(DEBUG_MODE_ENABLE)
	  	if(debugLevel > 1)
			{
		    DEBUG_SERIAL.println();
		    DEBUG_SERIAL.println(F("- Ping"));
		  }
	  #endif
	  */
  }

  else if (recvDtype == Range)  //Range
  {
  	receive_Range_Success = true;

    rangeLeft 	= (_completeData[1+_indexOffset] << 8) | (_completeData[0+_indexOffset]);
    rangeFront 	= (_completeData[3+_indexOffset] << 8) | (_completeData[2+_indexOffset]);
    rangeRight 	= (_completeData[5+_indexOffset] << 8) | (_completeData[4+_indexOffset]);
    rangeRear 	= (_completeData[7+_indexOffset] << 8) | (_completeData[6+_indexOffset]);
    rangetop 		= (_completeData[9+_indexOffset] << 8) | (_completeData[8+_indexOffset]);
    rangeBottom = (_completeData[11+_indexOffset] << 8) |(_completeData[10+_indexOffset]);
  }

  else if (recvDtype == Altitude)  //Altitude
  {
		receive_Altitude_Success = true;

		convertType.b[0] = _completeData[0+_indexOffset];
		convertType.b[1] = _completeData[1+_indexOffset];
		convertType.b[2] = _completeData[2+_indexOffset];
		convertType.b[3] = _completeData[3+_indexOffset];
		altitude_temperature = convertType.f;

		convertType.b[0] = _completeData[4+_indexOffset];
		convertType.b[1] = _completeData[5+_indexOffset];
		convertType.b[2] = _completeData[6+_indexOffset];
		convertType.b[3] = _completeData[7+_indexOffset];
		altitude_pressure = convertType.f;

		convertType.b[0] = _completeData[8+_indexOffset];
		convertType.b[1] = _completeData[9+_indexOffset];
		convertType.b[2] = _completeData[10+_indexOffset];
		convertType.b[3] = _completeData[11+_indexOffset];
		altitude_altitude = convertType.f;

		convertType.b[0] = _completeData[12+_indexOffset];
		convertType.b[1] = _completeData[13+_indexOffset];
		convertType.b[2] = _completeData[14+_indexOffset];
		convertType.b[3] = _completeData[15+_indexOffset];
		altitude_rangeHeight = convertType.f;

		/*
	   #if	defined(DEBUG_MODE_ENABLE)
	    if(debugLevel > 1)
			{
				DEBUG_SERIAL.println();
		    DEBUG_SERIAL.println(F("- Altitude"));
 				DEBUG_SERIAL.print(F("temperature\t"));
		    DEBUG_SERIAL.println(altitude_temperature,5);

		    DEBUG_SERIAL.print(F("pressure\t"));
		    DEBUG_SERIAL.println(altitude_pressure);

		    DEBUG_SERIAL.print(F("altitude\t"));
		    DEBUG_SERIAL.println(altitude_altitude,5);

		    DEBUG_SERIAL.print(F("rangeHeight\t"));
		    DEBUG_SERIAL.println(altitude_rangeHeight,3);
			}
		#endif
		*/
  }

  else if (recvDtype == State)  //State
  {
  	receive_State_Success = true;

    modeSystem 				= _completeData[0+_indexOffset];
    modeFlight 				= _completeData[1+_indexOffset];
    modeControlFlight = _completeData[2+_indexOffset];
    modeMovement 			= _completeData[3+_indexOffset];
    headless 					= _completeData[4+_indexOffset];
    controlSpeed 			= _completeData[5+_indexOffset];
    sensorOrientation = _completeData[6+_indexOffset];
    battery 					= _completeData[7+_indexOffset];

    /*
    #if	defined(DEBUG_MODE_ENABLE)
	    if(debugLevel > 1)
			{
		    DEBUG_SERIAL.println();
		    DEBUG_SERIAL.println(F("- State"));

		    DEBUG_SERIAL.print(F("modeSystem\t"));
		    DEBUG_SERIAL.println(modeSystem);

		    DEBUG_SERIAL.print(F("modeFlight\t"));
		    DEBUG_SERIAL.println(modeFlight);

		    DEBUG_SERIAL.print(F("modeControlFlight\t"));
		    DEBUG_SERIAL.println(modeControlFlight);

		    DEBUG_SERIAL.print(F("modeMovement\t"));
		    DEBUG_SERIAL.println(modeMovement);

		    DEBUG_SERIAL.print(F("headless\t"));
		    DEBUG_SERIAL.println(headless);

		    DEBUG_SERIAL.print(F("sensorOrientation\t"));
		    DEBUG_SERIAL.println(sensorOrientation);

		    DEBUG_SERIAL.print(F("battery\t"));
		    DEBUG_SERIAL.println(battery);
	  	}
  	#endif
  	*/
  }

  else if (recvDtype == RawFlow)  //RawFlow
  {
  	receive_RawFlow_Success = true;

  	convertType.b[0] = _completeData[0+_indexOffset];
		convertType.b[1] = _completeData[1+_indexOffset];
		convertType.b[2] = _completeData[2+_indexOffset];
		convertType.b[3] = _completeData[3+_indexOffset];
		rawFlowX = convertType.f;

		convertType.b[0] = _completeData[4+_indexOffset];
		convertType.b[1] = _completeData[5+_indexOffset];
		convertType.b[2] = _completeData[6+_indexOffset];
		convertType.b[3] = _completeData[7+_indexOffset];
		rawFlowY = convertType.f;

  	/*
  	#if	defined(DEBUG_MODE_ENABLE)
	  if(debugLevel > 1)
		{
				DEBUG_SERIAL.println();
		    DEBUG_SERIAL.println(F("- RawFlow"));
 				DEBUG_SERIAL.print(F("rawFlowX\t"));
		    DEBUG_SERIAL.println(rawFlowX);
		    DEBUG_SERIAL.print(F("rawFlowY\t"));
		    DEBUG_SERIAL.println(rawFlowY);
  	}
  	#endif
  	*/
  }
  else if (recvDtype == Trim)  //Trim
  {
  	receive_Trim_Success = true;

    trimRoll 			= (_completeData[1+_indexOffset] << 8) | (_completeData[0+_indexOffset]);
    trimPitch 		= (_completeData[3+_indexOffset] << 8) | (_completeData[2+_indexOffset]);
    trimYaw 			= (_completeData[5+_indexOffset] << 8) | (_completeData[4+_indexOffset]);
    trimThrottle 	= (_completeData[7+_indexOffset] << 8) | (_completeData[6+_indexOffset]);

    /*
		#if	defined(DEBUG_MODE_ENABLE)
		  if(debugLevel > 1)
			{
   			DEBUG_SERIAL.println();
		    DEBUG_SERIAL.println(F("- Trim"));

		    DEBUG_SERIAL.print(F("trimRoll\t"));
		    DEBUG_SERIAL.println(trimRoll);

		    DEBUG_SERIAL.print(F("trimPitch\t"));
		    DEBUG_SERIAL.println(trimPitch);

		    DEBUG_SERIAL.print(F("trimYaw\t"));
		    DEBUG_SERIAL.println(trimYaw);

		    DEBUG_SERIAL.print(F("trimThrottle\t"));
		    DEBUG_SERIAL.println(trimThrottle);
			}
  	#endif
  	*/
  }

  else if (recvDtype == Attitude)  //Attitude
  {
  	receive_Attitude_Success = true;

 		imuAngleRoll 	= (_completeData[1+_indexOffset] << 8) | (_completeData[0+_indexOffset]);
    imuAnglePitch = (_completeData[3+_indexOffset] << 8) | (_completeData[2+_indexOffset]);
    imuAngleYaw 	= (_completeData[5+_indexOffset] << 8) | (_completeData[4+_indexOffset]);

    /*
 		#if	defined(DEBUG_MODE_ENABLE)
			if(debugLevel > 1)
			{
		    DEBUG_SERIAL.println();
		    DEBUG_SERIAL.println(F("- Attitude"));

		    DEBUG_SERIAL.print(F("AngleRoll\t"));
		    DEBUG_SERIAL.println(imuAngleRoll);

		    DEBUG_SERIAL.print(F("AnglePitch\t"));
		    DEBUG_SERIAL.println(imuAnglePitch);

		    DEBUG_SERIAL.print(F("AngleYaw\t"));
		    DEBUG_SERIAL.println(imuAngleYaw);
		  }
	 	#endif
  	*/
  }


  else if (recvDtype == Motion)  //Motion
  {
		receive_Motion_Success = true;

    imuAccX 			= (_completeData[1+_indexOffset] << 8) 	| (_completeData[0+_indexOffset]);
    imuAccY 			= (_completeData[3+_indexOffset] << 8) 	| (_completeData[2+_indexOffset]);
    imuAccZ 			= (_completeData[5+_indexOffset] << 8) 	| (_completeData[4+_indexOffset]);

    imuGyroRoll   = (_completeData[7+_indexOffset] << 8) 	| (_completeData[6+_indexOffset]);
    imuGyroPitch  = (_completeData[9+_indexOffset] << 8) 	| (_completeData[8+_indexOffset]);
    imuGyroYaw    = (_completeData[11+_indexOffset] << 8) | (_completeData[10+_indexOffset]);

    imuAngleRoll  = (_completeData[13+_indexOffset] << 8) | (_completeData[12+_indexOffset]);
    imuAnglePitch = (_completeData[15+_indexOffset] << 8) | (_completeData[14+_indexOffset]);
    imuAngleYaw   = (_completeData[17+_indexOffset] << 8) | (_completeData[16+_indexOffset]);

    /*
    #if	defined(DEBUG_MODE_ENABLE)
			if(debugLevel > 1)
			{
		    DEBUG_SERIAL.println();
		    DEBUG_SERIAL.println(F("- MOTION");

		    DEBUG_SERIAL.print(F("AccX\t"));
		    DEBUG_SERIAL.println(imuAccX);

		    DEBUG_SERIAL.print(F("AccY\t"));
		    DEBUG_SERIAL.println(imuAccY);

		    DEBUG_SERIAL.print(F("AccZ\t"));
		    DEBUG_SERIAL.println(imuAccZ);

		    DEBUG_SERIAL.print(F("GyroRoll\t"));
		    DEBUG_SERIAL.println(imuGyroRoll);

		    DEBUG_SERIAL.print(F("GyroPitch\t"));
		    DEBUG_SERIAL.println(imuGyroPitch);

		    DEBUG_SERIAL.print(F("GyroYaw \t"));
		    DEBUG_SERIAL.println(imuGyroYaw);

		    DEBUG_SERIAL.print(F("AngleRoll\t"));
		    DEBUG_SERIAL.println(imuAngleRoll);

		    DEBUG_SERIAL.print(F("AnglePitch\t"));
		    DEBUG_SERIAL.println(imuAnglePitch);

		    DEBUG_SERIAL.print(F("AngleYaw\t"));
		    DEBUG_SERIAL.println(imuAngleYaw);
		  }
	 #endif
	 */
  }

  else if (recvDtype == RawMotion)  //RawMotion
  {
  	receive_RawMotion_Success = true;

  	rawImuAccX 				= (_completeData[1+_indexOffset] << 8) | (_completeData[0+_indexOffset]);
    rawImuAccY 				= (_completeData[3+_indexOffset] << 8) | (_completeData[2+_indexOffset]);
    rawImuAccZ 				= (_completeData[5+_indexOffset] << 8) | (_completeData[4+_indexOffset]);

    rawImuGyroRoll   	= (_completeData[7+_indexOffset] << 8) | (_completeData[6+_indexOffset]);
    rawImuGyroPitch 	= (_completeData[9+_indexOffset] << 8) | (_completeData[8+_indexOffset]);
    rawImuGyroYaw    	= (_completeData[11+_indexOffset] << 8)| (_completeData[10+_indexOffset]);

    /*
   	#if	defined(DEBUG_MODE_ENABLE)
			if(debugLevel > 1)
			{
		    DEBUG_SERIAL.println();
		    DEBUG_SERIAL.println(F("- MOTION"));

		    DEBUG_SERIAL.print(F("RAW AccX\t"));
		    DEBUG_SERIAL.println(rawImuAccX);

		    DEBUG_SERIAL.print(F("RAW AccY\t"));
		    DEBUG_SERIAL.println(rawImuAccY);

		    DEBUG_SERIAL.print(F("RAW AccZ\t"));
		    DEBUG_SERIAL.println(rawImuAccZ);

		    DEBUG_SERIAL.print(F("RAW GyroRoll\t"));
		    DEBUG_SERIAL.println(rawImuGyroRoll);

		    DEBUG_SERIAL.print(F("RAW GyroPitch\t"));
		    DEBUG_SERIAL.println(rawImuGyroPitch);

		    DEBUG_SERIAL.print(F("RAW GyroYaw \t"));
		    DEBUG_SERIAL.println(rawImuGyroYaw);
		  }
		#endif
		*/
  }

  else if (recvDtype == Position)  //Position
  {
		convertType.b[0] = _completeData[0+_indexOffset];
		convertType.b[1] = _completeData[1+_indexOffset];
		convertType.b[2] = _completeData[2+_indexOffset];
		convertType.b[3] = _completeData[3+_indexOffset];
		posX = convertType.f;

		convertType.b[0] = _completeData[4+_indexOffset];
		convertType.b[1] = _completeData[5+_indexOffset];
		convertType.b[2] = _completeData[6+_indexOffset];
		convertType.b[3] = _completeData[7+_indexOffset];
		posY = convertType.f;

		convertType.b[0] = _completeData[8+_indexOffset];
		convertType.b[1] = _completeData[9+_indexOffset];
		convertType.b[2] = _completeData[10+_indexOffset];
		convertType.b[3] = _completeData[11+_indexOffset];
		posZ = convertType.f;

  	/*
  	#if	defined(DEBUG_MODE_ENABLE)
			if(debugLevel > 1)
			{
   			DEBUG_SERIAL.println("");
		    DEBUG_SERIAL.println(F("- position"));

		    DEBUG_SERIAL.print(F("positionX\t"));
		    DEBUG_SERIAL.println(posX);

		    DEBUG_SERIAL.print(F("posY\t"));
		    DEBUG_SERIAL.println(posY);

		    DEBUG_SERIAL.print(F("positionZ\t"));
		    DEBUG_SERIAL.println(posZ);
  	  }
		#endif
		*/
  }


 	else if (recvDtype == Count)  //Count
  {
  	receive_Count_Success = true;


/*
count.timeFlight = BitConverter.ToUInt64(_data, 0);


count.countTakeOff = BitConverter.ToUInt16(_data, 8);
count.countLanding = BitConverter.ToUInt16(_data, 10);
count.countAccident = BitConverter.ToUInt16(_data, 12);


timeSystem	uint32_t	4 Byte	-	시스템 동작 시간(sec)
timeFlight	uint32_t	4 Byte	-	비행 시간(sec)


*/

  //	uint64_t timeData[8];
	//	for(int i = 0; i <= 7; i++)	timeData[i] = _completeData[i+_indexOffset];

  //	uint64_t timeFlight = ((timeData[7] << 512)|(timeData[6] << 256)|(timeData[5] << 128)|(timeData[4] << 64)|(timeData[3] << 32)|(timeData[2] << 16)|(timeData[1] << 8)|(timeData[0]));
		uint32_t timeFlight = ((_completeData[3+_indexOffset] << 32)|(_completeData[2+_indexOffset] << 16)|(_completeData[1+_indexOffset] << 8)|(_completeData[0+_indexOffset]));

		float milSec = (timeFlight % 1000)*0.001;
		timeFlight = timeFlight / 1000;
		timeHour=  timeFlight / 3600;
		timeMinute = (timeFlight % 3600) / 60;
		timeSec = (timeFlight % 60) +  milSec;

  	countTakeOff   = (_completeData[9+_indexOffset] << 8)  | (_completeData[8+_indexOffset]);
  	countLanding   = (_completeData[11+_indexOffset] << 8) | (_completeData[10+_indexOffset]);
  	countAccident  = (_completeData[13+_indexOffset] << 8) | (_completeData[12+_indexOffset]);

  	/*
  	#if	defined(DEBUG_MODE_ENABLE)
		  if(debugLevel > 1)
			{
 				DEBUG_SERIAL.println("");
		    DEBUG_SERIAL.println(F("- Count"));

		    DEBUG_SERIAL.print(F("timeFlight\t"));
		   // DEBUG_SERIAL.println(timeFlight);
				DEBUG_SERIAL.println();

		    DEBUG_SERIAL.print(F("countTakeOff\t"));
		    DEBUG_SERIAL.println(countTakeOff);

		    DEBUG_SERIAL.print(F("countLanding\t"));
		    DEBUG_SERIAL.println(countLanding);

		    DEBUG_SERIAL.print(F("countAccident\t"));
		    DEBUG_SERIAL.println(countAccident);
			}
		#endif
	*/
  }

  else if (recvDtype == InformationAssembledForController)  //Altitude
  {
  	receive_InformationAssembledForController_Success = true;

    imuAngleRoll  = _completeData[0+_indexOffset];
    imuAnglePitch = _completeData[1+_indexOffset];
    imuAngleYaw   = (_completeData[3+_indexOffset] << 8) | (_completeData[2+_indexOffset]);

    rpm 					= (_completeData[5+_indexOffset] << 8) | (_completeData[4+_indexOffset]);

    posX 					= (_completeData[7+_indexOffset] << 8) | (_completeData[6+_indexOffset]);
    posY 					= (_completeData[9+_indexOffset] << 8) | (_completeData[8+_indexOffset]);
    posZ 					= (_completeData[11+_indexOffset] << 8)| (_completeData[10+_indexOffset]);

    speedX 				= _completeData[12+_indexOffset];
    speedY 				= _completeData[13+_indexOffset];

   	altitude_rangeHeight = _completeData[14+_indexOffset];

    rssi = _completeData[15+_indexOffset];

  	/*
    #if	defined(DEBUG_MODE_ENABLE)
	    if(debugLevel > 1)
			{
		    DEBUG_SERIAL.println("");
		    DEBUG_SERIAL.println(F("- InformationAssembledForController"));

		    DEBUG_SERIAL.print(F("angleRoll\t"));
		    DEBUG_SERIAL.println(imuAngleRoll);

		    DEBUG_SERIAL.print(F("anglePitch\t"));
		    DEBUG_SERIAL.println(imuAnglePitch);

		    DEBUG_SERIAL.print(F("angleYaw\t"));
		    DEBUG_SERIAL.println(imuAngleYaw);

		    DEBUG_SERIAL.print(F("rpm\t\t"));
		    DEBUG_SERIAL.println(rpm);

		    DEBUG_SERIAL.print(F("positionX\t"));
		    DEBUG_SERIAL.println(posX);

		    DEBUG_SERIAL.print(F("positionY\t"));
		    DEBUG_SERIAL.println(posY);

		    DEBUG_SERIAL.print(F("positionZ\t"));
		    DEBUG_SERIAL.println(posZ);

		    DEBUG_SERIAL.print(F("speedX\t\t"));
		    DEBUG_SERIAL.println(speedX);

		    DEBUG_SERIAL.print(F("speedY\t\t"));
		    DEBUG_SERIAL.println(speedY);

		    DEBUG_SERIAL.print(F("range\t\t"));
		    DEBUG_SERIAL.println(altitude_rangeHeight);

		    DEBUG_SERIAL.print(F("rssi\t\t"));
		    DEBUG_SERIAL.println(rssi);
	  	}
  	#endif
  	*/
  }

  else if (recvDtype == Error)  //Error
  {
  	receive_Err_Success = true;

		errSensor[0] = _completeData[8+_indexOffset];
		errSensor[1] = _completeData[9+_indexOffset];
		errSensor[2] = _completeData[10+_indexOffset];
		errSensor[3] = _completeData[11+_indexOffset];

		errState[0] = _completeData[12+_indexOffset];
		errState[1] = _completeData[13+_indexOffset];
		errState[2] = _completeData[14+_indexOffset];
		errState[3] = _completeData[15+_indexOffset];

		/*
	  #if	defined(DEBUG_MODE_ENABLE)
	  if(debugLevel > 1)
		{
	    DEBUG_SERIAL.println();
	    DEBUG_SERIAL.println(F("- Error"));
	    DEBUG_SERIAL.print(F("errSensor\t"));

			for(int i = 0; i < 4 ; i++)
			{
				DEBUG_SERIAL.print(errSensor[i],HEX);
				DEBUG_SERIAL.print("\t");
			}
			DEBUG_SERIAL.println();

	    DEBUG_SERIAL.print(F("errState\t"));
			for(int i = 0; i < 4 ; i++)
			{
				DEBUG_SERIAL.print(errState[i],HEX);
				DEBUG_SERIAL.print("\t");
			}
			DEBUG_SERIAL.println();
  	}
	  #endif
	    	*/
  }

  else if (recvDtype == Motor)  //Motor
  {
  	receive_Motor_Success = true;

		rotationM0 	= _completeData[0+_indexOffset];
		valueM0		 	= (_completeData[2+_indexOffset] << 8) | (_completeData[1+_indexOffset]);

		rotationM1 	= _completeData[3+_indexOffset];
		valueM1 		= (_completeData[5+_indexOffset] << 8) | (_completeData[4+_indexOffset]);

		rotationM2 	= _completeData[6+_indexOffset];
		valueM2 		= (_completeData[8+_indexOffset] << 8) | (_completeData[7+_indexOffset]);

		rotationM3 	= _completeData[9+_indexOffset];
		valueM3 		= (_completeData[11+_indexOffset] << 8) | (_completeData[10+_indexOffset]);

	/*
	  #if	defined(DEBUG_MODE_ENABLE)
	  if(debugLevel > 1)
		{
	    DEBUG_SERIAL.println();
	    DEBUG_SERIAL.println(F("- Motor"));

	    DEBUG_SERIAL.print(F("M0 - Rotation\t"));
	    DEBUG_SERIAL.println(rotationM0);
	    DEBUG_SERIAL.print(F("M0 - Value\t"));
	    DEBUG_SERIAL.println(valueM0);

	    DEBUG_SERIAL.print(F("M1 - Rotation\t"));
	    DEBUG_SERIAL.println(rotationM1);
	    DEBUG_SERIAL.print(F("M1 - Value\t"));
	    DEBUG_SERIAL.println(valueM1);

	    DEBUG_SERIAL.print(F("M2 - Rotation\t"));
	    DEBUG_SERIAL.println(rotationM2);
	    DEBUG_SERIAL.print(F("M2 - Value\t"));
	    DEBUG_SERIAL.println(valueM2);

	    DEBUG_SERIAL.print(F("M3 - Rotation\t"));
	    DEBUG_SERIAL.println(rotationM3);
	    DEBUG_SERIAL.print(F("M3 - Value\t"));
	    DEBUG_SERIAL.println(valueM3);
  	}
	  #endif
	*/
  }
}

//-----------------------------------------------------------------------------------------------------------//
//------------------------------------------- sendProcess ---------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

void CoDrone2Class::sendProcess(byte _cType, byte _length, ...)
{
	byte data[50];
  byte _crc[2];

  data[0] = _cType;
  data[1] = (byte)_length;

  data[2] = 0xa0;		// From	Tester      = 0xA0,     // 테스터
  data[3] = 0x10;		// to  	Drone       = 0x10,     // 드론(Server)

	int index = 4;
	byte *ptr = &_length;
	for(int i = 1; i <= _length ; i++)
	{
		byte	_temp  = *(ptr + i);
  	data[index++] = _temp;
	}

//-------------------------------------------------------------------//
  unsigned short crcCal = CRC16_Make(data, _length + 4);
  _crc[0] = (crcCal >> 8) & 0xff;
  _crc[1] = crcCal & 0xff;
//-------------------------------------------------------------------//
  byte _packet[50];

  _packet[0] = START1;
  _packet[1] = START2;

  //HEADER & DATA
  for (int i = 0; i < _length + 5 ; i++)  _packet[i + 2] = data[i];

  //CRC
  _packet[_length + 6] = _crc[1];
  _packet[_length + 7] = _crc[0];
  _packet[_length + 8] = 0xff;

  if(isSendData)
  {
  	DRONE_SERIAL.write(_packet,  _length + 9);
  //	if(uartControlMode == 0) DRONE_SERIAL.write(packet,  _length + 9);
  //	else if(uartControlMode == 1) REMOCON_SERIAL.write(packet,  _length + 9);
  }
//-------------------------------------------------------------------//
	verifySendSuccess(_packet, _length);
//-------------------------------------------------------------------//

	#if	defined(DEBUG_MODE_ENABLE)

	//DEBUG_SERIAL.write(packet,  _length + 9);

	/*
	for(int i = 0; i < _length + 9; i++)
	{
	 DEBUG_SERIAL.print(packet[i],HEX);
	 DEBUG_SERIAL.print(" ");
  }
  DEBUG_SERIAL.println();
 */
	#endif
}

//-----------------------------------------------------------------------------------------------------------//
//----------------------------------------- verifySendSuccess -----------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

void CoDrone2Class::verifySendSuccess(byte _packet[], byte _length)
{
	if(verifyRepeatNum > 0)
	{
		boolean	_ack = recvGetDataProcess(Ack);

		while(!_ack)
		{
			if(isSendData)
			{
				DRONE_SERIAL.write(_packet,  _length + 9);
		  	//if(uartControlMode == 0) DRONE_SERIAL.write(_packet,  _length + 9);
		  	//else if(uartControlMode == 1) REMOCON_SERIAL.write(_packet,  _length + 9);
			}
			_ack = recvGetDataProcess(Ack);
			if (--verifyRepeatNum <= 0)
			{
				#if	defined(DEBUG_MODE_ENABLE)
					DEBUG_SERIAL.println(F("send failed"));
				#endif
				break; //time out check
			}
		}
	}
	verifyRepeatNum = 5;
}

//-----------------------------------------------------------------------------------------------------------//
//-------------------------------------------- receiveGetData -----------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

void CoDrone2Class::recvGetData(byte _type)
{
	verifyRepeatNum = 0;
	sendProcess(Request, 1, _type); //command, length,_type
	recvGetDataProcess(_type);
}

boolean CoDrone2Class::recvGetDataProcess(byte _reqType)
{
	byte *_reqCheckType;

	//---------------------------------------------------------------------------------------------------//
	if (_reqType == Altitude) 			_reqCheckType = &receive_Altitude_Success;
	else if (_reqType == State) 		_reqCheckType = &receive_State_Success;
	else if (_reqType == RawFlow) 	_reqCheckType = &receive_RawFlow_Success;
	else if (_reqType == Trim) 			_reqCheckType = &receive_Trim_Success;
	else if (_reqType == Motion) 		_reqCheckType = &receive_Motion_Success;
	else if (_reqType == RawMotion) _reqCheckType = &receive_RawFlow_Success;
	else if (_reqType == Attitude) 	_reqCheckType = &receive_Attitude_Success;
	else if (_reqType == Position) 	_reqCheckType = &receive_Position_Success;
	else if (_reqType == Count) 		_reqCheckType = &receive_Count_Success;

	else if (_reqType == Motor) 		_reqCheckType = &receive_Motor_Success;
	else if (_reqType == InformationAssembledForController) 		_reqCheckType = &receive_InformationAssembledForController_Success;

	else if (_reqType == Ack) 		_reqCheckType = &receive_Ack_Success;

	else if (_reqType == Range) 	_reqCheckType = &receive_Range_Success;

	//--------------------------------------------------------------------------------------------------//

	*_reqCheckType = 0;

	long oldTime = millis();

	while(!*_reqCheckType)
	{
	//	receive();
		if (oldTime + 25 < millis()) break; //time out check
	}

	return *_reqCheckType;
}

//-------------------------------------------------------------------------------------------------------//
//----------------------------------------  CRC checksum  -----------------------------------------------//
//-------------------------------------------------------------------------------------------------------//
	static const unsigned short crc16tab[256] = {
	  0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
	  0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
	  0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
	  0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
	  0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
	  0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
	  0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
	  0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
	  0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
	  0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
	  0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
	  0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
	  0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
	  0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
	  0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
	  0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
	  0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
	  0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
	  0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
	  0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
	  0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
	  0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	  0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
	  0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
	  0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
	  0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
	  0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
	  0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
	  0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
	  0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
	  0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
	  0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
	};

	unsigned short CoDrone2Class::CRC16_Make(unsigned char *buf, int len) //CRC16-CCITT Format
	{
	  unsigned short crc = 0 ;
	  for (int counter = 0; counter < len; counter++) crc = (crc << 8) ^ crc16tab[((crc >> 8) ^ * (char *)buf++) & 0x00FF];
	  return crc;
	}

	boolean CoDrone2Class::CRC16_Check(unsigned char data[], int len, unsigned char crc[])
	{
	  boolean crcCheck = false;
	
	  unsigned short receiveCRC = ((crc[1] << 8) | (crc[0] & 0xff));
	  unsigned short makeCRC = CRC16_Make(data, len + 2);
	
	  if (receiveCRC == makeCRC)        crcCheck = true;
	
	  return crcCheck;
	}

//----------------------------------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------------------------//
//-------------------------------------- For CodeLoader2 ------------------------------------------------//
//----------------------------------------- Variable ----------------------------------------------------//
//-------------------------------------------------------------------------------------------------------//

//---------------------------------------- Time Check ---------------------------------------------------//

//volatile int pingTimecheck = 0;
volatile int nowTimeLimit = 0;
volatile int timeLimitSet = 100;

//------------------------------------ Mode Select & Action ---------------------------------------------//

volatile boolean runProgram = false;
volatile boolean SerialToBluetooth = false;

volatile int deviceStop = 0;
volatile int deviceLand = 0;
volatile int deviceError = 0;
//--------------------------------------- Key Interrupt -------------------------------------------------//


volatile boolean funtionKeyState1 = false;
volatile boolean funtionKeyState2 = false;
volatile int funtionkeyPush1 = 0;
volatile int funtionkeyPush2 = 0;

//----------------------------------------- Display LED -------------------------------------------------//

volatile int TimerBasicFlag = 0;
volatile int TimerFlagDuration = 0;

volatile byte ledSequence = 4;
volatile boolean ledSetate = true;
volatile boolean ledState_1 = false, ledState_2 = false, ledState_3 = false, ledState_4 = false;
volatile boolean ledState[4] = {false, false, false, false};
//-------------------------------------------------------------------------------------------------------//




//-------------------------------------------------------------------------------------------------------//
//-------------------------------------- For CodeLoader2 ------------------------------------------------//
//----------------------------------------- Funtion -----------------------------------------------------//
//-------------------------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------------------------//
//-------------------------------------------- Timer2 ---------------------------------------------------//
//-------------------------------------------------------------------------------------------------------//
ISR(TIMER2_OVF_vect)
//ISR(TIMER1_OVF_vect)	  //TCNT1 = 0xFB80 ; // 9999  us	10ms
{
  TCNT2 =  0xB8;  //10 ms

  //--------------------------- Receive Data	 ------------------------------//

  if (!SerialToBluetooth) CoDrone2.receive();

  //--------------------------- Button Check -------------------------------//

  funtionKeyState1 == true ? funtionkeyPush1++: funtionkeyPush1 = 0;
  funtionKeyState2 == true ? funtionkeyPush2++: funtionkeyPush2 = 0;

  //------------------------------------------------------------------------//

	if (!runProgram && !SerialToBluetooth)	FuntionKeyLED();		// push button LED action sequence
	else LEDToggle();

  //------------------------------------------------------------------------//

  if(runProgram)
  {
		////////////////비행을 eeprom으로 동작할수 있도록 /////////////////////////
		////////////////비행 기록Flight memory /////////////////////////
		////////////////센서 기록 memory /////////////////////////
		////////////////좌표이동 /////////////////////////
		////////////////마지막 비행에 대한 정보를 켰을때 보여줌 /////////////////////////

	 	if (TimerBasicFlag == 50)	//every 50 * 10 ms
		{
			//---------------------- VERIFY_COMMUNICATION ------------//
			CoDrone2.verifyRepeatNum = 0; 			
  		CoDrone2.pingCheck();		  		
  		//-------------------- Check Error -------------------//
			CheckErrorStatus();
		}
		
		if (TimerFlagDuration == 9)	//every 10 * 10 ms
		{				
			
			TimerFlagDuration = 0;
			
			//------ begin에 입력한 시간을 체크하여 착륙 시킴 --------//
			CheckFlightDuration();							
			//------------------- Check StopButton -------------------//
			ChekStopButton();				
		}		
		else		TimerFlagDuration++;	
		
   	//----------------------------------------------------------//
	}
	
  //------------------------------------------------------------------------//

}

//-------------------------------------------------------------------------------------------------------//


void CheckErrorStatus()
{
	if(deviceError == 0)
	{
		if(CoDrone2.receive_Err_Success == true)
		{
			CoDrone2.receive_Err_Success = false;

			if((CoDrone2.errSensor[0] > 0)	||	(CoDrone2.errSensor[1] > 0)	||	(CoDrone2.errSensor[2] > 0)	||	(CoDrone2.errSensor[3] > 0))	deviceError = 1;
			if((CoDrone2.errState[0] > 0)		||	(CoDrone2.errState[1] > 0)	||	(CoDrone2.errState[2] > 0)	||	(CoDrone2.errState[3] > 0))		deviceError = deviceError + 2;
		}
	}
 	//----------------------------------------------------------//

 	else	if (deviceError > 0 && deviceError < 5)
	{
		EEPROM.write(EEP_ERR_CHECK, 1);

		if(deviceError & 0b01 == 1)
		{
			#if	defined(DEBUG_MODE_ENABLE)
		//	DEBUG_SERIAL.println(F("Err Sen..."));
			#endif

			timeLimitSet = 0;
			deviceLand = 1;

			 EEPROM.write(EEP_ERR_SENS0, CoDrone2.errSensor[0]);
			 EEPROM.write(EEP_ERR_SENS1, CoDrone2.errSensor[1]);
			 EEPROM.write(EEP_ERR_SENS2, CoDrone2.errSensor[2]);
			 EEPROM.write(EEP_ERR_SENS3, CoDrone2.errSensor[3]);
		}

		else if(deviceError & 0b10 == 1)
		{
			#if	defined(DEBUG_MODE_ENABLE)
		//	DEBUG_SERIAL.println(F("Err Sta..."));
			#endif

			timeLimitSet = 0;
			deviceLand = 1;

			 EEPROM.write(EEP_ERR_STATE0, CoDrone2.errState[0]);
			 EEPROM.write(EEP_ERR_STATE1, CoDrone2.errState[1]);
			 EEPROM.write(EEP_ERR_STATE2, CoDrone2.errState[2]);
			 EEPROM.write(EEP_ERR_STATE3, CoDrone2.errState[3]);
		}

		deviceError = 5;
	}
}

void CheckFlightDuration()
{
	if(deviceLand < 1)
	{
		if (timeLimitSet > 0)
		{
			if(++nowTimeLimit >= timeLimitSet)
			{
				#if	defined(DEBUG_MODE_ENABLE)
			//	DEBUG_SERIAL.println(F("timeOut..."));
				#endif
		
				timeLimitSet = 0;
				deviceLand = 1;	//Stop Timer
			}
		}
	}

 	else //	if (deviceLand > 0)
	{
		CoDrone2.isSendData = false;
		digitalWrite(6, HIGH);
		deviceLand ++;
		
	  //	if (!(deviceLand % 10))
		if (deviceLand < 5)
		{
			CoDrone2.isSendData = true;
			CoDrone2.verifyRepeatNum = 0;
			CoDrone2.land();
			CoDrone2.isSendData = false;
		}

		else if (deviceLand >= 5)
		{
			#if	defined(DEBUG_MODE_ENABLE)
		//	DEBUG_SERIAL.println(F("land..."));
			#endif

			CoDrone2.isSendData = true;
			CoDrone2.verifyRepeatNum = 0;
			CoDrone2.land();
			CoDrone2.isSendData = false;

			SoundForTimer(700, 2);
			SoundForTimer(350, 2);
			SoundForTimer(700, 2);
			SoundForTimer(350, 2);
			SoundForTimer(100, 2);

	   	deviceLand = 0;
		}
		
	}
}

//--------------------------------------------------------//

void ChekStopButton()
{
  if (deviceStop > 0)
	{
		timeLimitSet = 0;

		CoDrone2.isSendData = false;
		digitalWrite(6, HIGH);
		
		deviceStop ++;
		
		//if (!(deviceStop % 10))
		if (deviceStop <= 5)
		{
			CoDrone2.isSendData = true;
			CoDrone2.verifyRepeatNum = 0;
			CoDrone2.emergencyStop();

			CoDrone2.isSendData = false;
		}

		//else if (deviceStop > 50)
		else if (deviceStop > 5)
		{
			#if	defined(DEBUG_MODE_ENABLE)
		//	DEBUG_SERIAL.println(F("stop..."));
			#endif

			// for (int i = 0 ; i < 500; i++)	SoundFX(2000.0, 20);
			// Sound_Alarm();

			CoDrone2.isSendData = true;

			CoDrone2.verifyRepeatNum = 0;
			CoDrone2.emergencyStop();

			CoDrone2.isSendData = false;

			SoundForTimer(700, 2);
			SoundForTimer(350, 2);
			SoundForTimer(700, 2);
			SoundForTimer(350, 2);
			SoundForTimer(100, 2);

			wdt_disable();
	    wdt_enable(WDTO_500MS);
	    while (1) {}
		}
	}
		
	else if(funtionkeyPush1 > 50)	deviceStop = 1;	
}

//--------------------------------------------------------//



//----------------------------------- LED -------------------------------------------//

void LEDToggle()
{
	if (TimerBasicFlag == 100)	//100*10ms
	{
		ledSetate == true? ledSetate = false: ledSetate = true;

		if(ledSetate)
		{
			if(SerialToBluetooth)		 PORTD |= 0b10000000;
			else if(runProgram)			 PORTD |= 0b00100000;
		}
		else
		{
			if(SerialToBluetooth)		 PORTD &= ~0b10000000;
			else if(runProgram)			 PORTD &= ~0b00100000;
		}
		TimerBasicFlag = 0;
	}
	else  TimerBasicFlag++;
}

void FuntionKeyLED()
{
  if ((funtionkeyPush1 > 115) || (funtionkeyPush2 > 115))
  {
  	if(funtionkeyPush1 > 115)
  	{
  		runProgram = true;
    	funtionKeyState1 = 0;
    	funtionkeyPush1 = 0;
  	}
  	else if  (funtionkeyPush2 > 115)
  	{
  		SerialToBluetooth = true;
  		funtionKeyState2 = 0;
    	funtionkeyPush2 = 0;
  	}
    ledSetate = false;
    digitalWrite(LED1, ledSetate);
    digitalWrite(LED2, ledSetate);
    digitalWrite(LED3, ledSetate);
    digitalWrite(LED4, ledSetate);
  }

  //------------------------------------------------------------------------//
  else if((funtionkeyPush1 > 0) || (funtionkeyPush2 > 0))
  {
    if (TimerBasicFlag == 25)
    {
      if(ledSequence < 8)
      {
        ledSetate = true;
        digitalWrite(ledSequence++, ledSetate);
      }
      TimerBasicFlag = 0;
    }
    else  TimerBasicFlag++;
  }
  //------------------------------------------------------------------------//
  else
  {
    ledSetate = false;
    digitalWrite(LED1, ledSetate);
    digitalWrite(LED2, ledSetate);
    digitalWrite(LED3, ledSetate);
    digitalWrite(LED4, ledSetate);
    TimerBasicFlag = 0;
    ledSequence = 4;
  }
}


  //---------------------------------------------------------------------------------------------------//


//--------------------------------- Sound -----------------------------------------//

void Sound_Alarm()
{
  int melody[] = {2537};
  int tempo[] = {8};
  SoundProcess(melody, tempo, 1);
}

void SoundForTimer(long frequency, int tempo)
{
	int length = 2000/tempo;  //TEMPO
	long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
	long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing

	for (long i=0; i < numCycles; i++)
	{
  	digitalWrite(BUZZER, HIGH);
		delayMicroseconds(delayValue); // wait for the calculated delay value
	  digitalWrite(BUZZER, LOW);
		delayMicroseconds(delayValue); // wait again or the calculated delay value
	}
}

void SoundFX(float amplitude, float period)
{
  int uDelay = 2 + amplitude + amplitude * sin(millis() / period);

  for (int i = 0; i < 5; i++)
  {
    digitalWrite(BUZZER, HIGH);
    delayMicroseconds(uDelay);
    digitalWrite(BUZZER, LOW);
    delayMicroseconds(uDelay);
  }
}

/*
//soundFX(5000.0, 100); // sonic screwdriver
 //soundFX(3000.0, 30); // sonic screwdriver
 //soundFX(100.0,30.0); // ray gun
 //soundFX(3.0,30.0); // star trek
 //soundFX(1.0,30.0); // star trek high
*/

void SoundProcess(int _melody[], int _tempo[], int _size)
{
  for (int thisNote = 0; thisNote < _size; thisNote++)
  {
    int noteDuration = 1000 / _tempo[thisNote];
    tone(BUZZER, _melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
}


//-------------------------------------------------------------------------------------------------------//
//--------------------------------------- initailize & begin --------------------------------------------//
//-------------------------------------------------------------------------------------------------------//

void CodeLoader2Init(float time)
{
	//-------------------------------- Pin Set -------------------------------------//

	pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

	pinMode(BUZZER, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  DRONE_SERIAL.begin(57600);

  #if	defined(DEBUG_MODE_ENABLE)
 	DEBUG_SERIAL.begin(57600);
  #endif

 //-------------------------------- LED MOVE ---------------------------------------//

	for(int i = 4;i < 8; i++)
	{
		digitalWrite(i, HIGH);
		delay(80);
	}
	for(int i = 7; i > 3; i--)
	{
		digitalWrite(i, LOW);
		delay(80);
	}

	//----------------------------- Start Sound ------------------------------------//

  for (int i = 0 ; i < 300; i++)	SoundFX(5000.0, 100);

  //----------------------------- interrupt set ----------------------------------//

  pinMode(SW1, INPUT);
  attachInterrupt(digitalPinToInterrupt(SW1), FuntionKeyCheck1, CHANGE);
  pinMode(SW2, INPUT);
  attachInterrupt(digitalPinToInterrupt(SW2), FuntionKeyCheck2, CHANGE);




  //---------------------------- Debug -------------------------------//
  	/*
	   #if	defined(DEBUG_MODE_ENABLE)
	    if(CoDrone2.debugLevel > 1)
			{
				DEBUG_SERIAL.println();

		    DEBUG_SERIAL.print(F("EEP_ERR_Debug0\t"));
		    DEBUG_SERIAL.println(EEPROM.read(EEP_ERR_Debug0));

		    DEBUG_SERIAL.print(F("EEP_ERR_Debug1\t"));
		    DEBUG_SERIAL.println(EEPROM.read(EEP_ERR_Debug1));

		    DEBUG_SERIAL.print(F("EEP_ERR_Debug2\t"));
		    DEBUG_SERIAL.println(EEPROM.read(EEP_ERR_Debug2));

		    DEBUG_SERIAL.print(F("EEP_ERR_Debug3\t"));
		    DEBUG_SERIAL.println(EEPROM.read(EEP_ERR_Debug3));


				convertType.b[0] = EEPROM.read(EEP_ERR_Debug0);
				convertType.b[1] = EEPROM.read(EEP_ERR_Debug1);
				convertType.b[2] = EEPROM.read(EEP_ERR_Debug2);
				convertType.b[3] = EEPROM.read(EEP_ERR_Debug3);

				DEBUG_SERIAL.print(F("0,1,2,3 data \t"));
		    DEBUG_SERIAL.println(convertType.f);

		    DEBUG_SERIAL.print(F("EEP_ERR_Debug4\t"));
		    DEBUG_SERIAL.println(EEPROM.read(EEP_ERR_Debug4));

		    DEBUG_SERIAL.print(F("EEP_ERR_Debug5\t"));
		    DEBUG_SERIAL.println(EEPROM.read(EEP_ERR_Debug5));

		    DEBUG_SERIAL.print(F("EEP_ERR_Debug6\t"));
		    DEBUG_SERIAL.println(EEPROM.read(EEP_ERR_Debug6));

		    DEBUG_SERIAL.print(F("EEP_ERR_Debug7\t"));
		    DEBUG_SERIAL.println(EEPROM.read(EEP_ERR_Debug7));

				convertType.b[0] = EEPROM.read(EEP_ERR_Debug4);
				convertType.b[1] = EEPROM.read(EEP_ERR_Debug5);
				convertType.b[2] = EEPROM.read(EEP_ERR_Debug6);
				convertType.b[3] = EEPROM.read(EEP_ERR_Debug7);

				DEBUG_SERIAL.print(F("4,5,6,7 data \t"));
		    DEBUG_SERIAL.println(convertType.f);

			}
		#endif
		*/

  //---------------------------- Check for errors during flight -------------------------------//

	if (EEPROM.read(EEP_ERR_CHECK) == true)
	{
		DEBUG_SERIAL.println(F("- Error occurred during flight"));
		DEBUG_SERIAL.print(F("Sensor\t"));
		uint32_t _errSensor = ((EEPROM.read(EEP_ERR_SENS3) << 32)|(EEPROM.read(EEP_ERR_SENS2) << 16)|(EEPROM.read(EEP_ERR_SENS1) << 8)|(EEPROM.read(EEP_ERR_SENS0)));
		DEBUG_SERIAL.print(_errSensor,HEX);
		DEBUG_SERIAL.print(F("\t"));


		//bit flag 비교문으로 변경 예정
		if(_errSensor == ErrorSensorNone) 											DEBUG_SERIAL.println(F("ErrorSensorNone"));
		else if(_errSensor == Motion_NoAnswer) 									DEBUG_SERIAL.println(F("Motion_NoAnswer"));
		else if(_errSensor == Motion_WrongValue) 								DEBUG_SERIAL.println(F("Motion_WrongValue"));
		else if(_errSensor == Motion_NotCalibrated) 						DEBUG_SERIAL.println(F("Motion_NotCalibrated"));
		else if(_errSensor == Motion_Calibrating) 							DEBUG_SERIAL.println(F("Motion_Calibrating"));
		else if(_errSensor == Pressure_NoAnswer) 								DEBUG_SERIAL.println(F("Pressure_NoAnswer"));
		else if(_errSensor == Pressure_WrongValue) 							DEBUG_SERIAL.println(F("Pressure_WrongValue"));
		else if(_errSensor == RangeGround_NoAnswer) 						DEBUG_SERIAL.println(F("RangeGround_NoAnswer"));
		else if(_errSensor == RangeGround_WrongValue) 					DEBUG_SERIAL.println(F("RangeGround_WrongValue"));
		else if(_errSensor == Flow_NoAnswer) 										DEBUG_SERIAL.println(F("Flow_NoAnswer"));
		else if(_errSensor == Flow_WrongValue) 									DEBUG_SERIAL.println(F("Flow_WrongValue"));
		else if(_errSensor == Flow_CannotRecognizeGroundImage)	DEBUG_SERIAL.println(F("Flow_CannotRecognizeGroundImage"));

	  DEBUG_SERIAL.print(F("State\t"));
		uint32_t _errState = ((EEPROM.read(EEP_ERR_STATE3) << 32)|(EEPROM.read(EEP_ERR_STATE2) << 16)|(EEPROM.read(EEP_ERR_STATE1) << 8)|(EEPROM.read(EEP_ERR_STATE0)));
		DEBUG_SERIAL.print(_errState,HEX);
	  DEBUG_SERIAL.print(F("\t"));

	  //bit flag 비교문으로 변경 예정
		if(_errState == ErrorStateNone) 																	DEBUG_SERIAL.println(F("ErrorStateNone"));
		else if(_errState == NotRegistered) 															DEBUG_SERIAL.println(F("NotRegistered"));
		else if(_errState == FlashReadLock_UnLocked) 											DEBUG_SERIAL.println(F("FlashReadLock_UnLocked"));
		else if(_errState == Motion_NotCalibrated) 												DEBUG_SERIAL.println(F("Motion_NotCalibrated"));
		else if(_errState == BootloaderWriteLock_UnLocked) 								DEBUG_SERIAL.println(F("BootloaderWriteLock_UnLocked"));
		else if(_errState == TakeoffFailure_CheckPropellerAndMotor) 			DEBUG_SERIAL.println(F("TakeoffFailure_CheckPropellerAndMotor"));
		else if(_errState == CheckPropellerVibration) 										DEBUG_SERIAL.println(F("CheckPropellerVibration"));
	}

 	//------------------------------------------------------------------------------//

/*
  //----------------------------- timer1 set -------------------------------------//

  TIMSK1 &= ~(1 << TOIE1);
  TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
  TCCR1B &= ~(1 << CS12);
  TCCR1B = ((1 << CS11) | (1 << CS10));
  TIMSK1 |= (1 << TOIE1);
*/

  //----------------------------- timer2 set -------------------------------------//

  TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20));    //1024
  TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
  TCCR2B &= ~(1 << WGM22);
  TCCR2A |= (1 << WGM21);
  TIMSK2 &= ~(1 << OCIE2B);
  TIMSK2 |= (1 << TOIE2);


  //---------------------------- Low Battery Check -------------------------------//


  byte LowBatLV = 50;
  byte _bat = CoDrone2.getBatteryPercentage();

// 

	#if	defined(DEBUG_MODE_ENABLE)
  	DEBUG_SERIAL.println(F("Battery Read..."));
  	DEBUG_SERIAL.print(_bat);
  	DEBUG_SERIAL.println("%");
	#endif

  if((_bat < LowBatLV) && (_bat != 0))
  {
  	
  	TIMSK2 &= ~(1 << TOIE2);
  	
  	#if	defined(DEBUG_MODE_ENABLE)
  		DEBUG_SERIAL.println(F("Battery needs to be charged"));
		#endif
		
 
  	boolean _ledState = false;

	 	for(int i = 0; i< 3; i++)
		{
  		Sound_Alarm();
			if (_ledState == false)   _ledState = true;
			else _ledState = false;
  		digitalWrite(LED1, _ledState);

  		delay(500);
		}
		

  TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20));    //1024
  TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
  TCCR2B &= ~(1 << WGM22);
  TCCR2A |= (1 << WGM21);
  TIMSK2 &= ~(1 << OCIE2B);
  TIMSK2 |= (1 << TOIE2);
 
  }




	#if	defined(DEBUG_MODE_ENABLE)
	//------------------------------------------------------------------------------//
	// Serial.println(F("- new start -"));
	//------------------------------------------------------------------------------//
	#endif

	//----------------------------- timeLimitSet -------------------------------------//
  timeLimitSet = time * 10;
	CoDrone2.isSendData = true;

	//------------------------------ Mode Check --------------------------------------//
	while(1)
	{
	 	if(SerialToBluetooth)	// Bluetooth Connetion Mode
		{
		//	for (int i = 0 ; i < 500; i++)	SoundFX(2400.0, 70);
		//	Sound_Beep1();

			int melody[] = {392, 523, 494, 523};
  		int tempo[] = {4, 4, 4,8};
  		SoundProcess(melody, tempo, 4);

			while(SerialToBluetooth)
			{
			  if (DEBUG_SERIAL.available())
			  {
			    int inByte = DEBUG_SERIAL.read();
			    #if	defined(DEBUG_MODE_ENABLE)
			   		 DRONE_SERIAL.write(inByte);
			    #endif
				}

				if (DRONE_SERIAL.available())
			  {
			    int inByte = DRONE_SERIAL.read();
			    #if	defined(DEBUG_MODE_ENABLE)
			   		 DEBUG_SERIAL.write(inByte);
			    #endif
				}
			}
		}
		else if (runProgram)		break;		//programmable Mode
	}


	//----------------------- SetControlFlightMode -------------------------//
	CoDrone2.setControlFlightMode(Position);	//position
	delay(50);
	//------------------------- SetHeadlessType ----------------------------//
  CoDrone2.setHeadlessType(2);  //Normal
 	delay(50);
  //---------------------------- setWeight -------------------------------//
	//	CoDrone2.setWeight(130);
	//	delay(50);
  //---------------------------- clearBias -------------------------------//
  CoDrone2.clearBias();
  //----------------------------------------------------------------------//

/*
	//---------------------------------------------------------------//

	EEPROM.write(EEP_ERR_Debug0, 0);
	EEPROM.write(EEP_ERR_Debug1, 0);
	EEPROM.write(EEP_ERR_Debug2, 0);
	EEPROM.write(EEP_ERR_Debug3, 0);

	EEPROM.write(EEP_ERR_Debug4, 0);
	EEPROM.write(EEP_ERR_Debug5, 0);
	EEPROM.write(EEP_ERR_Debug6, 0);
	EEPROM.write(EEP_ERR_Debug7, 0);
	*/
	//---------------------------------------------------------------//

	 EEPROM.write(EEP_ERR_CHECK, 0);

	 EEPROM.write(EEP_ERR_SENS0, 0);
	 EEPROM.write(EEP_ERR_SENS1, 0);
	 EEPROM.write(EEP_ERR_SENS2, 0);
	 EEPROM.write(EEP_ERR_SENS3, 0);

	 EEPROM.write(EEP_ERR_STATE0, 0);
	 EEPROM.write(EEP_ERR_STATE1, 0);
	 EEPROM.write(EEP_ERR_STATE2, 0);
	 EEPROM.write(EEP_ERR_STATE3, 0);

	delay(1000);

	//------------------------------ LostConnectionSet --------------------------------------//

	//CoDrone2.lostConnectionSet(2000, 3000, 5000);	// Time out Set

	//---------------------------------------------------------------------------------------//

	#if	defined(DEBUG_MODE_ENABLE)
	//	DEBUG_SERIAL.println(F("- begin -"));
	#endif

  for (int i = 0 ; i < 200; i++)	SoundFX(1000.0, 20);

  nowTimeLimit = 0;
}

//-------------------------------------------------------------------------------------------------------//
//----------------------------------------- Key Interrupt -----------------------------------------------//
//-------------------------------------------------------------------------------------------------------//
	void FuntionKeyCheck1()
	{
	  funtionKeyState1 = !digitalRead(SW1);
	}
	void FuntionKeyCheck2()
	{
	  funtionKeyState2 = !digitalRead(SW2);
	}
//-------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------//
