/*
 Hekulex.cpp - Library for Dongbu Herkulex DRS-0101/DRS-0201 
 Copyright (c) 2012 - http://robottini.altervista.org
 Created by Alessandro on 09/12/2012.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,  
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
 *****************************************************************************
    PLEASE START READING: Herkulex Servo Manual (http://www.hovis.co.kr/guide/herkulexeng.pdf)
 *****************************************************************************
 
 IMPORTANT:

  The library works on Arduino UNO/2009 - Arduino Mega.
  Please with Arduino UNO/2009 works with SoftwareSerial library modified with baud rate 57.600.
  Use this begin type:
		begin(57600, int rx, int tx);
 
  For Arduino Mega, please use baud rate 115.200

 *****************************************************************************
 Contact: alegiaco@gmail.com
 Web:     http://robottini.altervista.org
 Autor:   Alessandro Giacomel
 *****************************************************************************  

 Modified 8 May 2014 by Jaehong (jhoh@robolink.co.kr)

*/

#include "Herkulex.h"
//#include "SoftwareSerial.h"


// Macro for the Serial port selection
#define HSerial1     1 		// Write in Serial 1 port Arduino Mega - Pin 19(rx) - 18 (tx) 
#define HSerial2     2   	// Write in Serial 2 port Arduino Mega - Pin 17(rx) - 16 (tx) 
#define HSerial3     3   	// Write in Serial 3 port Arduino Mega - Pin 15(rx) - 14 (tx)
#define SSerial      4   	// Write in SoftSerial Arduino with 328p or Mega
 
//extern SoftwareSerial Serial(2, 3);

// Herkulex begin with Arduino Uno
void HerkulexClass::begin(long baud)
{
	Serial.begin(baud);
	/*
	SwSerial.setRX(rx);
	SwSerial.setTX(tx);
	SwSerial.begin(baud);
	*/
	port = SSerial;
}

#if defined (__AVR_ATmega128__)
// Herkulex begin with Arduino Mega - Serial 1
void HerkulexClass::beginSerial1(long baud)
{
	Serial1.begin(baud);
	port = HSerial1;
}


#elif defined (__AVR_ATmega1280__) || defined (__AVR_ATmega2560__)
// Herkulex begin with Arduino Mega - Serial 1
void HerkulexClass::beginSerial1(long baud)
{
	Serial1.begin(baud);
	port = HSerial1;
}

// Herkulex begin with Arduino Mega - Serial 2
void HerkulexClass::beginSerial2(long baud)
{
	Serial2.begin(baud);
	port = HSerial2;
}

// Herkulex begin with Arduino Mega - Serial 3
void HerkulexClass::beginSerial3(long baud)
{
	Serial3.begin(baud);
	port = HSerial3;
}

#endif

// Herkulex end
void HerkulexClass::end()
{
	switch (port)
	{
	case SSerial:
		Serial.end();
		break;
		
    #if defined (__AVR_ATmega128__)
	case HSerial1:
		Serial1.end();
		break;
		
    #elif defined (__AVR_ATmega1280__) || defined (__AVR_ATmega2560__)
    	case HSerial1:
		Serial1.end();
		break;
	case HSerial2:
		Serial2.end();
		break;
	case HSerial3:
		Serial3.end();
		break;
		
	#endif
	}
}

// initialize servos
void HerkulexClass::initialize()
{
	conta=0;
	LengthString=0;
    delay(100);       
    clearError(BROADCAST_ID);	// clear error for all servos
    delay(10);
    ACK(1);						// set ACK
    delay(10);
    torqueON(BROADCAST_ID);		// torqueON for all servos
    delay(10);		
}

// stat
int HerkulexClass::stat(int servoID)
{
	pSize    = 0x07;			//3.Packet size
	pID      = servoID;			//4.Servo ID - 0XFE=All servos
	cmd      = HSTAT;			//5.CMD

	ck1=(pSize^pID^cmd)&0xFE;
    ck2=(~ck1)&0xFE; 
  
	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	     
	sendData(dataEx, pSize);
	if(readData(9) < 9)		// read 9 bytes from serial
		return -3;

	
	pSize = dataEx[2];           // 3.Packet size 7-58
	pID   = dataEx[3];           // 4. Servo ID
	cmd   = dataEx[4];           // 5. CMD
	data[0]=dataEx[7];
    data[1]=dataEx[8];
    LengthString=2;
	
    ck1 = (dataEx[2]^dataEx[3]^dataEx[4]^dataEx[7]^dataEx[8]) & 0xFE;
	ck2 = checksum2(ck1);
	
	if (ck1 != dataEx[5])
		return -1; //checksum verify

	if (ck2 != dataEx[6])
		return -2;

	return (int)dataEx[7];			// return status
}

// torque on - 
void HerkulexClass::torqueON(int servoID)
{
	pSize = 0x0A;               // 3.Packet size 7-58
	pID   = servoID;            // 4. Servo ID
	cmd   = HRAMWRITE;          // 5. CMD
	data[0]=0x34;               // 8. Address
	data[1]=0x01;               // 9. Length
	data[2]=0x60;               // 10. 0x60=Torque ON
	LengthString=3;             // LengthData
  	
	ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command Ram Write
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	dataEx[7] = data[0]; 		// Address 52
	dataEx[8] = data[1]; 		// Length
	dataEx[9] = data[2]; 		// Torque ON

	sendData(dataEx, pSize);
}

// torque off - the torque is FREE, not Break
void HerkulexClass::torqueOFF(int servoID)
{
	pSize = 0x0A;               // 3.Packet size 7-58
	pID   = servoID;            // 4. Servo ID
	cmd   = HRAMWRITE;          // 5. CMD
	data[0]=0x34;               // 8. Address
	data[1]=0x01;               // 9. Length
	data[2]=0x00;               // 10. 0x00=Torque Free
	LengthString=3;             // LengthData
  	
	ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command Ram Write
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	dataEx[7] = data[0]; 		// Address 52
	dataEx[8] = data[1]; 		// Length
	dataEx[9] = data[2]; 		// Torque Free

    sendData(dataEx, pSize);

}

// ACK  - 0=No Replay, 1=Only reply to READ CMD, 2=Always reply
void HerkulexClass::ACK(int valueACK)
{
	pSize = 0x0A;               // 3.Packet size 7-58
	pID   = 0xFE;	            // 4. Servo ID
	cmd   = HRAMWRITE;          // 5. CMD
	data[0]=0x34;               // 8. Address
	data[1]=0x01;               // 9. Length
	data[2]=valueACK;           // 10.Value. 0=No Replay, 1=Only reply to READ CMD, 2=Always reply
	LengthString=3;             // LengthData
  	
	ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command Ram Write
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	dataEx[7] = data[0]; 		// Address 52
	dataEx[8] = data[1]; 		// Length
	dataEx[9] = data[2]; 		// Value

 	sendData(dataEx, pSize);
}

// model - 1=0101 - 2=0201
byte HerkulexClass::model()
{
	pSize = 0x09;               // 3.Packet size 7-58
	pID   = 0xFE;	            // 4. Servo ID
	cmd   = HEEPREAD;           // 5. CMD
	data[0]=0x00;               // 8. Address
	data[1]=0x01;               // 9. Length
	LengthString=2;             // LengthData
  	
	ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command Ram Write
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	dataEx[7] = data[0]; 		// Address
	dataEx[8] = data[1]; 		// Length

    sendData(dataEx, pSize);
	if(readData(9) < 9)		// read 9 bytes from serial
		return 0;
	
	pSize = dataEx[2];           // 3.Packet size 7-58
	pID   = dataEx[3];           // 4. Servo ID
	cmd   = dataEx[4];           // 5. CMD
	data[0]=dataEx[7];           // 8. 1st byte
	LengthString=1;              // LengthData
  	
	ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

	if (ck1 != dataEx[5]) return -1; //checksum verify
	if (ck2 != dataEx[6]) return -2;
		
	return dataEx[7];			// return status

}

// setID - Need to restart the servo
void HerkulexClass::set_ID(int ID_Old, int ID_New)
{
	pSize = 0x0A;               // 3.Packet size 7-58
	pID   = ID_Old;		        // 4. Servo ID OLD - original servo ID
	cmd   = HEEPWRITE;          // 5. CMD
	data[0]=0x06;               // 8. Address
	data[1]=0x01;               // 9. Length
	data[2]=ID_New;             // 10. ServoID NEW
	LengthString=3;             // LengthData
  	
	ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command Ram Write
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	dataEx[7] = data[0]; 		// Address 52
	dataEx[8] = data[1]; 		// Length
	dataEx[9] = data[2]; 		// Value

	sendData(dataEx, pSize);
}

// clearError
void HerkulexClass::clearError(int servoID)
{
	pSize = 0x0B;               // 3.Packet size 7-58
	pID   = servoID;     		// 4. Servo ID - 253=all servos
	cmd   = HRAMWRITE;          // 5. CMD
	data[0]=0x30;               // 8. Address
	data[1]=0x02;               // 9. Length
	data[2]=0x00;               // 10. Write error=0
	data[3]=0x00;               // 10. Write detail error=0
	
	LengthString=4;             // LengthData
  	
	ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command Ram Write
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	dataEx[7] = data[0]; 		// Address 52
	dataEx[8] = data[1]; 		// Length
	dataEx[9] = data[2]; 		// Value1
	dataEx[10]= data[3]; 		// Value2

	sendData(dataEx, pSize);
}

// move all servo at the same time to a position: servo list building
void HerkulexClass::moveAll(int servoID, int Goal, int iLed)
{
	  if (Goal > 1023 || Goal < 0)
		return;						 //0 <--> 1023 range
	  
	  int iMode=0;                   //mode=position
	  int iStop=0;                   //stop=0
	  

	  // Position definition
	  int posLSB=Goal & 0X00FF;					// MSB Pos
	  int posMSB=(Goal & 0XFF00) >> 8;			// LSB Pos

	  //led 
	  int iBlue=0;
	  int iGreen=0;
	  int iRed=0;
	  switch (iLed) {
	  case 1:
		iGreen=1;
		break;
	  case 2:
		iBlue=1;
		break;
	  case 3:
		iRed=1;
		break;
	  }
	  
	  int SetValue=iStop+iMode*2+iGreen*4+iBlue*8+iRed*16;	//assign led value

	  addData(posLSB, posMSB, SetValue, servoID);	//add servo data to list, pos mode
}

// move all servo at the same time to a position: servo list building
void HerkulexClass::moveAllAngle(int servoID, float angle, int iLed)
{
	if (angle > 160.0|| angle < -160.0) return; // out of the range	
	int position = (int)(angle/0.325) + 512;
	moveAll(servoID, position, iLed);
}

// move all servo at the same time with different speeds: servo list building
void HerkulexClass::moveSpeedAll(int servoID, int Goal, int iLed)
{
	  if (Goal > 1023 || Goal < -1023)
		return;								 //-1023 <--> 1023 range

	  int iMode=1;                  		// mode=continous rotation
	  int iStop=0;                  		// Stop=0

	  // Speed definition
	  int GoalSpeedSign;
	  if (Goal < 0) {
		GoalSpeedSign = (-1)* Goal ;
		GoalSpeedSign |= 0x4000;  //bit n?4 
	  } 
	  else {
		GoalSpeedSign = Goal;
	  }

	  int speedGoalLSB=GoalSpeedSign & 0X00FF; 	      		 // MSB speedGoal 
	  int speedGoalMSB=(GoalSpeedSign & 0xFF00) >> 8;        // LSB speedGoal 

	  //led 
	  int iBlue=0;
	  int iGreen=0;
	  int iRed=0;
	  switch (iLed) {
	  case 1:
		iGreen=1;
		break;
	  case 2:
		iBlue=1;
		break;
	  case 3:
		iRed=1;
		break;
	  }

	  int SetValue=iStop+iMode*2+iGreen*4+iBlue*8+iRed*16;	//assign led value

	  addData(speedGoalLSB, speedGoalMSB, SetValue, servoID);		//add servo data to list, speed mode
}



// move all servo with the same execution time
void HerkulexClass::actionAll(int pTime)
{
	if ((pTime <0) || (pTime > 2856)) return;

    pSize = 0x08 + conta;     	    // 3.Packet size 7-58
	cmd   = HSJOG;		 			// 5. CMD SJOG Write n servo with same execution time
	playTime=int((float)pTime/11.2);// 8. Execution time
 
    pID=0xFE^playTime;
    ck1=checksum1(moveData,conta);	//6. Checksum1
	ck2=checksum2(ck1);				//7. Checksum2

    pID=0xFE;
	dataEx[0] = 0xFF;				// Packet Header
	dataEx[1] = 0xFF;				// Packet Header	
	dataEx[2] = pSize;	 			// Packet Size
	dataEx[3] = pID;				// Servo ID
	dataEx[4] = cmd;				// Command Ram Write
	dataEx[5] = ck1;				// Checksum 1
	dataEx[6] = ck2;				// Checksum 2
	dataEx[7] = playTime;			// Execution time	
	
	for (int i=0; i < conta; i++)
		dataEx[i+8]=moveData[i];	// Variable servo data

	sendData(dataEx, pSize);

	conta=0; 						//reset counter   
}



// get ram data
 int HerkulexClass::readRegistryRam(int servoID, int address, int writeByte) 
 {
int Position  = 0;

    	pSize = 0x09;               // 3.Packet size 7-58
	pID   = servoID;     	    // 4. Servo ID - 253=all servos
	cmd   = HRAMREAD;           // 5. CMD
	data[0]=address;               // 8. Address
	data[1]=writeByte;               // 9. Length
	
	LengthString=2;             // LengthData
  	
	ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command Ram Write
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	dataEx[7] = data[0];      	// Address  
	dataEx[8] = data[1]; 		// Length
	
	sendData(dataEx, pSize);
	
	
	pSize = 0x09;               // 3.Packet size 7-58
	pID   = 0xFE;	            // 4. Servo ID
	cmd   = HEEPREAD;           // 5. CMD
	data[0]=0x00;               // 8. Address
	data[1]=0x01;               // 9. Length
	LengthString=2;             // LengthData
  	
	ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command Ram Write
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	dataEx[7] = data[0]; 		// Address
	dataEx[8] = data[1]; 		// Length

    sendData(dataEx, pSize);
	
	
	
	/*
	if(readData(9) < 9)		// read 9 bytes from serial
	return -3;

	pSize = dataEx[2];           // 3.Packet size 7-58
	pID   = dataEx[3];           // 4. Servo ID
	cmd   = dataEx[4];           // 5. CMD
	data[0]=dataEx[7];
    	data[1]=dataEx[8];
    	LengthString=2;
	
    ck1 = (dataEx[2]^dataEx[3]^dataEx[4]^dataEx[7]^dataEx[8]) & 0xFE;
	ck2 = checksum2(ck1);
	
	if (ck1 != dataEx[5])
		return -1; //checksum verify

	if (ck2 != dataEx[6])
		return -2;

	return (int)dataEx[7];			// return status
	*/
	
	
	if(readData(13) < 13)		// read 9 bytes from serial
		return -1;
        	
	pSize = dataEx[2];           // 3.Packet size 7-58
	pID   = dataEx[3];           // 4. Servo ID
	cmd   = dataEx[4];           // 5. CMD
	data[0]=dataEx[7];
	data[1]=dataEx[8];
	data[2]=dataEx[9];
	data[3]=dataEx[10];
	data[4]=dataEx[11];
	data[5]=dataEx[12];
	LengthString=6;

    ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

    if (ck1 != dataEx[5]) return -1;
	if (ck2 != dataEx[6]) return -1;

	Position = ((dataEx[10]&0x03)<<8) | dataEx[9];
     //   return Position;	
        return dataEx[9];	//FIRST BYTE
//        return dataEx[8];	//SECOND BYTE
        
}




// get Position
 int HerkulexClass::getPosition(int servoID) {
	int Position  = 0;

    pSize = 0x09;               // 3.Packet size 7-58
	pID   = servoID;     	    // 4. Servo ID - 253=all servos
	cmd   = HRAMREAD;           // 5. CMD
	data[0]=0x3A;               // 8. Address
	data[1]=0x02;               // 9. Length
	
	LengthString=2;             // LengthData
  	
	ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command Ram Write
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	dataEx[7] = data[0];      	// Address  
	dataEx[8] = data[1]; 		// Length
	
	sendData(dataEx, pSize);
	if(readData(13) < 13)		// read 9 bytes from serial
		return -1;
        	
	pSize = dataEx[2];           // 3.Packet size 7-58
	pID   = dataEx[3];           // 4. Servo ID
	cmd   = dataEx[4];           // 5. CMD
	data[0]=dataEx[7];
    data[1]=dataEx[8];
    data[2]=dataEx[9];
    data[3]=dataEx[10];
    data[4]=dataEx[11];
    data[5]=dataEx[12];
    LengthString=6;

    ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

    if (ck1 != dataEx[5]) return -1;
	if (ck2 != dataEx[6]) return -1;

	Position = ((dataEx[10]&0x03)<<8) | dataEx[9];
        return Position;	
}

float HerkulexClass::getAngle(int servoID) {
	int pos = (int)getPosition(servoID);
	if(pos < 0)
		return -1;

	return (pos-512) * 0.325;
}

// reboot single servo - pay attention 253 - all servos doesn't work!
void HerkulexClass::reboot(int servoID) {
        
    pSize = 0x07;               // 3.Packet size 7-58
	pID   = servoID;     	    // 4. Servo ID - 253=all servos
	cmd   = HREBOOT;            // 5. CMD
    ck1=(pSize^pID^cmd)&0xFE;
    ck2=(~(pSize^pID^cmd))&0xFE ; ;	

	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command Ram Write
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	
	sendData(dataEx, pSize);
}

// LED  - see table of colors 
void HerkulexClass::setLed(int servoID, int valueLed)
{
	pSize   = 0x0A;               // 3.Packet size 7-58
	pID     = servoID;            // 4. Servo ID
	cmd     = HRAMWRITE;          // 5. CMD
	data[0] = 0x35;               // 8. Address 53
    data[1] = 0x01;               // 9. Length
	data[2] = valueLed;           // 10.LedValue
	LengthString=3;               // LengthData
  	  	
	ck1=checksum1(data,LengthString);	//6. Checksum1
	ck2=checksum2(ck1);					//7. Checksum2

	dataEx[0] = 0xFF;			// Packet Header
	dataEx[1] = 0xFF;			// Packet Header	
	dataEx[2] = pSize;	 		// Packet Size
	dataEx[3] = pID;			// Servo ID
	dataEx[4] = cmd;			// Command Ram Write
	dataEx[5] = ck1;			// Checksum 1
	dataEx[6] = ck2;			// Checksum 2
	dataEx[7] = data[0];        // Address
	dataEx[8] = data[1];       	// Length
	dataEx[9] = data[2];        // Value

	sendData(dataEx, pSize);
}

// get the speed for one servo - values betweeb -1023 <--> 1023
int HerkulexClass::getSpeed(int servoID) {
  int speedy  = 0;

  pSize = 0x09;               // 3.Packet size 7-58
  pID   = servoID;     	   	  // 4. Servo ID 
  cmd   = HRAMREAD;           // 5. CMD
  data[0]=0x40;               // 8. Address
  data[1]=0x02;               // 9. Length

  LengthString=2;             // LengthData

  ck1=checksum1(data,LengthString);		//6. Checksum1
  ck2=checksum2(ck1);					//7. Checksum2

  dataEx[0] = 0xFF;			// Packet Header
  dataEx[1] = 0xFF;			// Packet Header	
  dataEx[2] = pSize;		// Packet Size
  dataEx[3] = pID;			// Servo ID
  dataEx[4] = cmd;			// Command Ram Write
  dataEx[5] = ck1;			// Checksum 1
  dataEx[6] = ck2;			// Checksum 2
  dataEx[7] = data[0]; 	    // Address  
  dataEx[8] = data[1]; 		// Length

  sendData(dataEx, pSize);
  if(readData(13) < 13)		// read 13 bytes from serial
		return -1;
 
  pSize = dataEx[2];           // 3.Packet size 7-58
  pID   = dataEx[3];           // 4. Servo ID
  cmd   = dataEx[4];           // 5. CMD
  data[0]=dataEx[7];
  data[1]=dataEx[8];
  data[2]=dataEx[9];
  data[3]=dataEx[10];
  data[4]=dataEx[11];
  data[5]=dataEx[12];
  LengthString=6;

  ck1=checksum1(data,LengthString);	//6. Checksum1
  ck2=checksum2(ck1);				//7. Checksum2

  if (ck1 != dataEx[5]) return -1;
  if (ck2 != dataEx[6]) return -1;

  speedy = ((dataEx[10]&0xFF)<<8) | dataEx[9];
  return speedy;
}

// move one servo with continous rotation
void HerkulexClass::moveSpeedOne(int servoID, int Goal, int pTime, int iLed)
{
  if (Goal > 1023 || Goal < -1023) return;              // speed (goal) non correct
  if ((pTime <0) || (pTime > 2856)) return;

  int GoalSpeedSign;
  if (Goal < 0) {
    GoalSpeedSign = (-1)* Goal ;
    GoalSpeedSign |= 0x4000;  //bit n?4 
  } 
  else {
    GoalSpeedSign = Goal;
  }
  int speedGoalLSB=GoalSpeedSign & 0X00FF; 		       // MSB speedGoal 
  int speedGoalMSB=(GoalSpeedSign & 0xFF00) >> 8;      // LSB speedGoal 

  //led 
  int iBlue=0;
  int iGreen=0;
  int iRed=0;
  switch (iLed) {
  case 1:
    iGreen=1;
    break;
  case 2:
    iBlue=1;
    break;
  case 3:
    iRed=1;
    break;
  }
  int SetValue=2+iGreen*4+iBlue*8+iRed*16;		//assign led value 

  playTime=int((float)pTime/11.2);				// 8. Execution time

  pSize = 0x0C;              					// 3.Packet size 7-58
  cmd   = HSJOG;      					        // 5. CMD

  data[0]=speedGoalLSB;            			    // 8. speedLSB
  data[1]=speedGoalMSB;              			// 9. speedMSB
  data[2]=SetValue;                          	// 10. Mode=0;
  data[3]=servoID;                    			// 11. ServoID

  pID=servoID^playTime;

  LengthString=4;             					// LengthData

  ck1=checksum1(data,LengthString);				//6. Checksum1
  ck2=checksum2(ck1);							//7. Checksum2

  pID=servoID;

  dataEx[0] = 0xFF;				// Packet Header
  dataEx[1] = 0xFF;				// Packet Header	
  dataEx[2] = pSize;	 		// Packet Size
  dataEx[3] = pID;				// Servo ID
  dataEx[4] = cmd;				// Command Ram Write
  dataEx[5] = ck1;				// Checksum 1
  dataEx[6] = ck2;				// Checksum 2
  dataEx[7] = playTime;  		// Execution time	
  dataEx[8] = data[0];
  dataEx[9] = data[1];
  dataEx[10] = data[2];
  dataEx[11] = data[3];
  
  sendData(dataEx, pSize);
}

// move one servo at goal position 0 - 1024
void HerkulexClass::moveOne(int servoID, int Goal, int pTime, int iLed)
{
  if (Goal > 1023 || Goal < 0) return;              // speed (goal) non correct
  if ((pTime <0) || (pTime > 2856)) return;

  // Position definition
  int posLSB=Goal & 0X00FF;								// MSB Pos
  int posMSB=(Goal & 0XFF00) >> 8;						// LSB Pos

  //led 
  int iBlue=0;
  int iGreen=0;
  int iRed=0;
  switch (iLed) {
  case 1:
    iGreen=1;
    break;
  case 2:
    iBlue=1;
    break;
  case 3:
    iRed=1;
    break;
  }
  int SetValue=iGreen*4+iBlue*8+iRed*16;	//assign led value 

  playTime=int((float)pTime/11.2);			// 8. Execution time

  pSize = 0x0C;          			    	// 3.Packet size 7-58
  cmd   = HSJOG;              				// 5. CMD

  data[0]=posLSB;               			// 8. speedLSB
  data[1]=posMSB;               			// 9. speedMSB
  data[2]=SetValue;                         // 10. Mode=0;
  data[3]=servoID;                    		// 11. ServoID

    pID=servoID^playTime;

  LengthString=4;             				// LengthData

  ck1=checksum1(data,LengthString);			//6. Checksum1
  ck2=checksum2(ck1);						//7. Checksum2

  pID=servoID;

  dataEx[0] = 0xFF;				// Packet Header
  dataEx[1] = 0xFF;				// Packet Header	
  dataEx[2] = pSize;	 		// Packet Size
  dataEx[3] = pID;				// Servo ID
  dataEx[4] = cmd;				// Command Ram Write
  dataEx[5] = ck1;				// Checksum 1
  dataEx[6] = ck2;				// Checksum 2
  dataEx[7] = playTime;  		// Execution time	
  dataEx[8] = data[0];
  dataEx[9] = data[1];
  dataEx[10] = data[2];
  dataEx[11] = data[3];

  sendData(dataEx, pSize);
}

// move one servo to an angle between -160 and 160
void HerkulexClass::moveOneAngle(int servoID, float angle, int pTime, int iLed) {
	if (angle > 160.0|| angle < -160.0) return;	
	int position = (int)(angle/0.325) + 512;
	moveOne(servoID, position, pTime, iLed);
}

// write registry in the RAM: one byte 
void HerkulexClass::writeRegistryRAM(int servoID, int address, int writeByte)
{
  pSize = 0x0A;               	// 3.Packet size 7-58
  pID   = servoID;     			// 4. Servo ID - 253=all servos
  cmd   = HRAMWRITE;          	// 5. CMD
  data[0]=address;              // 8. Address
  data[1]=0x01;               	// 9. Length
  data[2]=writeByte;            // 10. Write error=0
 
  LengthString=3;             	// LengthData

  ck1=checksum1(data,LengthString);	//6. Checksum1
  ck2=checksum2(ck1);				//7. Checksum2

  dataEx[0] = 0xFF;			// Packet Header
  dataEx[1] = 0xFF;			// Packet Header	
  dataEx[2] = pSize;	 	// Packet Size
  dataEx[3] = pID;			// Servo ID
  dataEx[4] = cmd;			// Command Ram Write
  dataEx[5] = ck1;			// Checksum 1
  dataEx[6] = ck2;			// Checksum 2
  dataEx[7] = data[0]; 		// Address 52
  dataEx[8] = data[1]; 		// Length
  dataEx[9] = data[2]; 		// Value1
  dataEx[10]= data[3]; 		// Value2

  sendData(dataEx, pSize);
}

// write registry in the EEP memory (ROM): one byte 
void HerkulexClass::writeRegistryEEP(int servoID, int address, int writeByte)
{
  pSize = 0x0A;                  // 3.Packet size 7-58
  pID   = servoID;     	         // 4. Servo ID - 253=all servos
  cmd   = HEEPWRITE;             // 5. CMD
  data[0]=address;               // 8. Address
  data[1]=0x01;                  // 9. Length
  data[2]=writeByte;             // 10. Write error=0
 
  LengthString=3;           	 // LengthData

  ck1=checksum1(data,LengthString);	//6. Checksum1
  ck2=checksum2(ck1);				//7. Checksum2

  dataEx[0] = 0xFF;			// Packet Header
  dataEx[1] = 0xFF;			// Packet Header	
  dataEx[2] = pSize;		// Packet Size
  dataEx[3] = pID;			// Servo ID
  dataEx[4] = cmd;			// Command Ram Write
  dataEx[5] = ck1;			// Checksum 1
  dataEx[6] = ck2;			// Checksum 2
  dataEx[7] = data[0]; 		// Address 52
  dataEx[8] = data[1]; 		// Length
  dataEx[9] = data[2]; 		// Value1
  dataEx[10]= data[3]; 		// Value2

  sendData(dataEx, pSize);
}

/////////////////
//change modify 150121
void HerkulexClass::set_KP(int servoID, int writeByte)
{
	
 //ram write
  pSize = 0x0B;               	// 3.Packet size 7-58
  pID   = servoID;     			// 4. Servo ID - 253=all servos
  cmd   = HRAMWRITE;          	// 5. CMD
  data[0]=0x18;              // 8. Address
  data[1]=0x02;               	// 9. Length
  data[2]=writeByte;            // 10. Write error=0
 
  LengthString=3;             	// LengthData

  ck1=checksum1(data,LengthString);	//6. Checksum1
  ck2=checksum2(ck1);				//7. Checksum2

  dataEx[0] = 0xFF;			// Packet Header
  dataEx[1] = 0xFF;			// Packet Header	
  dataEx[2] = pSize;	 	// Packet Size
  dataEx[3] = pID;			// Servo ID
  dataEx[4] = cmd;			// Command Ram Write
  dataEx[5] = ck1;			// Checksum 1
  dataEx[6] = ck2;			// Checksum 2
  dataEx[7] = data[0]; 		// Address 52
  dataEx[8] = data[1]; 		// Length
  dataEx[9] = data[2]; 		// Value1
  dataEx[10]= data[3]; 		// Value2

  sendData(dataEx, pSize);
 
 //eep write

  pSize = 0x0B;                  // 3.Packet size 7-58
  pID   = servoID;     	         // 4. Servo ID - 253=all servos
  cmd   = HEEPWRITE;             // 5. CMD
  data[0]=0x1E;               // 8. Address
  data[1]=0x02;                  // 9. Length
  data[2]=writeByte;             // 10. Write error=0
 
  LengthString=3;           	 // LengthData

  ck1=checksum1(data,LengthString);	//6. Checksum1
  ck2=checksum2(ck1);				//7. Checksum2

  dataEx[0] = 0xFF;			// Packet Header
  dataEx[1] = 0xFF;			// Packet Header	
  dataEx[2] = pSize;		// Packet Size
  dataEx[3] = pID;			// Servo ID
  dataEx[4] = cmd;			// Command Ram Write
  dataEx[5] = ck1;			// Checksum 1
  dataEx[6] = ck2;			// Checksum 2
  dataEx[7] = data[0]; 		// Address 52
  dataEx[8] = data[1]; 		// Length
  dataEx[9] = data[2]; 		// Value1
  dataEx[10]= data[3]; 		// Value2

  sendData(dataEx, pSize);
}


/////////////////
void HerkulexClass::writeRegistryRAM_2byte(int servoID, int address,  int writeByte)
{
  pSize = 0x0B;               	// 3.Packet size 7-58
  pID   = servoID;     			// 4. Servo ID - 253=all servos
  cmd   = HRAMWRITE;          	// 5. CMD
  data[0]=address;              // 8. Address
  data[1]=0x02;               	// 9. Length
  data[2]=writeByte;            // 10. Write error=0
 
  LengthString=3;             	// LengthData

  ck1=checksum1(data,LengthString);	//6. Checksum1
  ck2=checksum2(ck1);				//7. Checksum2

  dataEx[0] = 0xFF;			// Packet Header
  dataEx[1] = 0xFF;			// Packet Header	
  dataEx[2] = pSize;	 	// Packet Size
  dataEx[3] = pID;			// Servo ID
  dataEx[4] = cmd;			// Command Ram Write
  dataEx[5] = ck1;			// Checksum 1
  dataEx[6] = ck2;			// Checksum 2
  dataEx[7] = data[0]; 		// Address 52
  dataEx[8] = data[1]; 		// Length
  dataEx[9] = data[2]; 		// Value1
  dataEx[10]= data[3]; 		// Value2

  sendData(dataEx, pSize);
}
//////////////////////
//change modify 150121
// write registry in the EEP memory (ROM): one byte 
void HerkulexClass::writeRegistryEEP_2byte(int servoID, int address, int writeByte)
{
  pSize = 0x13;                  // 3.Packet size 7-58
  pID   = servoID;     	         // 4. Servo ID - 253=all servos
  cmd   = HEEPWRITE;             // 5. CMD
  data[0]=address;               // 8. Address
  data[1]=0x0A;                  // 9. Length
  data[2]=writeByte;             // 10. Write error=0
 
  LengthString=3;           	 // LengthData

  ck1=checksum1(data,LengthString);	//6. Checksum1
  ck2=checksum2(ck1);				//7. Checksum2

  dataEx[0] = 0xFF;			// Packet Header
  dataEx[1] = 0xFF;			// Packet Header	
  dataEx[2] = pSize;		// Packet Size
  dataEx[3] = pID;			// Servo ID
  dataEx[4] = cmd;			// Command Ram Write
  dataEx[5] = ck1;			// Checksum 1
  dataEx[6] = ck2;			// Checksum 2
  dataEx[7] = data[0]; 		// Address 52
  dataEx[8] = data[1]; 		// Length
  dataEx[9] = data[2]; 		// Value1
  dataEx[10]= data[3]; 		// Value2

  sendData(dataEx, pSize);
}
////////////////////

void  HerkulexClass::maximumVin(int servoID, int voltage)
{
	writeRegistryRAM(servoID,0x07,voltage);
}

void  HerkulexClass::minimumVin(int servoID, int voltage)
{
	writeRegistryRAM(servoID,0x06,voltage);
}


// Private Methods //////////////////////////////////////////////////////////////

// checksum1
int HerkulexClass::checksum1(byte* data, int LengthString)
{
  XOR = 0;	
  XOR = XOR ^ pSize;
  XOR = XOR ^ pID;
  XOR = XOR ^ cmd;
  for (int i = 0; i < LengthString; i++) 
  {
    XOR = XOR ^ data[i];
  }
  return XOR&0xFE;
}


// checksum2
int HerkulexClass::checksum2(int XOR)
{
	return (~XOR)&0xFE;
}

// add data to variable list servo for syncro execution
void HerkulexClass::addData(int GoalLSB, int GoalMSB, int set, int servoID)
{
	moveData[conta++]=GoalLSB;  
	moveData[conta++]=GoalMSB;
	moveData[conta++]=set;
	moveData[conta++]=servoID;
}

// Sending the buffer long Length to Serial port
void HerkulexClass::sendData(byte* buffer, int Length)
{
	clearBuffer(); 		//clear the serialport buffer - try to do it!
    switch (port)
	{
		case SSerial:
			Serial.write(buffer, Length);
			Serial.flush();
			break;

		#if defined (__AVR_ATmega128__)
		case HSerial1:
			Serial1.write(buffer, Length);
			Serial1.flush();
			break;
				
		#elif defined (__AVR_ATmega1280__) || defined (__AVR_ATmega2560__)						
		case HSerial1:
			Serial1.write(buffer, Length);
			Serial1.flush();
			break;
		case HSerial2:
			Serial2.write(buffer, Length);
			Serial2.flush();
			break;
		case HSerial3:
			Serial3.write(buffer, Length);
			Serial3.flush();
			break;
		#endif
	}
}

// * Receiving the Length of bytes from Serial port
int HerkulexClass::readData(int size)
{
	int n = 0;	
    unsigned long preMillis = millis();

	switch (port)
	{
	case SSerial:
 		while (millis() - preMillis <= TIME_OUT)
		{
			boolean rcv = false;
			while(Serial.available() > 0)
			{
				byte inchar = (byte)Serial.read();
				if(n > 0)
				{
					if(inchar == 0xFF && dataEx[n-1] == 0xFF)
					{
						n = 0; 				 // if found new header, begin again
						dataEx[n++] = 0xFF;						
					}
				}
				dataEx[n++] = inchar;
				rcv = true;

				if(n >= size)
					break;				
			}

			if(n >= size)
				break;

			if(rcv == true)
				preMillis = millis();
		}
		break;
	
	#if defined (__AVR_ATmega128__)
	case HSerial1:		
		while (millis() - preMillis <= TIME_OUT)
		{
			boolean rcv = false;
			while(Serial1.available() > 0)
			{
				byte inchar = (byte)Serial1.read();
				if(n > 0)
				{
					if(inchar == 0xFF && dataEx[n-1] == 0xFF)
					{
						n = 0; 				 // if found new header, begin again
						dataEx[n++] = 0xFF;						
					}
				}
				dataEx[n++] = inchar;
				rcv = true;

				if(n >= size)
					break;				
			}

			if(n >= size)
				break;

			if(rcv == true)
				preMillis = millis();
		}
		break;
		
	#elif defined (__AVR_ATmega1280__) || defined (__AVR_ATmega2560__)
	case HSerial1:
		while (millis() - preMillis <= TIME_OUT)
		{
			boolean rcv = false;
			while(Serial1.available() > 0)
			{
				byte inchar = (byte)Serial1.read();
				if(n > 0)
				{
					if(inchar == 0xFF && dataEx[n-1] == 0xFF)
					{
						n = 0; 				 // if found new header, begin again
						dataEx[n++] = 0xFF;						
					}
				}
				dataEx[n++] = inchar;
				rcv = true;

				if(n >= size)
					break;				
			}

			if(n >= size)
				break;

			if(rcv == true)
				preMillis = millis();
		}
		break;
		
	case HSerial2:
	    while (millis() - preMillis <= TIME_OUT)
		{
			boolean rcv = false;
			while(Serial2.available() > 0)
			{
				byte inchar = (byte)Serial2.read();
				if(n > 0)
				{
					if(inchar == 0xFF && dataEx[n-1] == 0xFF)
					{
						n = 0; 				 // if found new header, begin again
						dataEx[n++] = 0xFF;						
					}
				}
				dataEx[n++] = inchar;
				rcv = true;

				if(n >= size)
					break;				
			}

			if(n >= size)
				break;

			if(rcv == true)
				preMillis = millis();
		}
		break;

	case HSerial3:
		while (millis() - preMillis <= TIME_OUT)
		{
			boolean rcv = false;
			while(Serial3.available() > 0)
			{
				byte inchar = (byte)Serial3.read();
				if(n > 0)
				{
					if(inchar == 0xFF && dataEx[n-1] == 0xFF)
					{
						n = 0; 				 // if found new header, begin again
						dataEx[n++] = 0xFF;						
					}
				}
				dataEx[n++] = inchar;
				rcv = true;

				if(n >= size)
					break;				
			}

			if(n >= size)
				break;

			if(rcv == true)
				preMillis = millis();
		}
		break;
		
	#endif
	}

	return n;
}

//clear buffer in the serial port - better - try to do this
void HerkulexClass::clearBuffer()
{
	switch (port)
	{
	case SSerial:
		Serial.flush();
        while (Serial.available()){
			Serial.read();
		}
        break;

	#if defined (__AVR_ATmega128__)
	case HSerial1:
		Serial1.flush();
		while (Serial1.available()){
			Serial1.read();
		}
		break;
		
	#elif defined (__AVR_ATmega1280__) || defined (__AVR_ATmega2560__)
	case HSerial1:
		Serial1.flush();
		while (Serial1.available()){
			Serial1.read();
		}
		break;

	case HSerial2:
	    Serial2.flush();
		while (Serial2.available()){
			Serial2.read();
		}
		break;
	case HSerial3:
	    Serial3.flush();
		while (Serial3.available()){
			Serial3.read();
		}
		break;
		
	#endif
	}
}

void HerkulexClass::printHexByte(byte x)
{
	Serial.print("0x");
	if (x < 16) {
	  Serial.print('0');
	}
	Serial.print(x, HEX);
    Serial.print(" ");
}

HerkulexClass Herkulex;