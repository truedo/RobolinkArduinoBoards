/*
	CoDrone2.h - CoDrone2 library
	Copyright (C) 2014 RoboLink.  All rights reserved.
	LastUpdate : 2018-11-13
*/

#ifndef CoDrone2_h
#define CoDrone2_h
#include "Arduino.h"
//#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <EEPROM.h>


//-------------------------------------------------------------------------------------------------------//
//-------------------------------------- For CodeLoader2 ------------------------------------------------//
//-------------------------------------------------------------------------------------------------------//

#define LED1  4
#define LED2  5
#define LED3  6
#define LED4  7
#define SW1 2
#define SW2 3
#define BUZZER 8

//-------------------------------------------------------------------------------------------------------//
//---------------------------------------- EEPROM ADDRESS -----------------------------------------------//
//-------------------------------------------------------------------------------------------------------//

#define EEP_LAST_STATE 				11
#define EEP_LAST_FLIGHT_EVENT 12
#define EEP_COMMAND_LIST			13

#define EEP_ERR_CHECK					20

#define EEP_ERR_SENS0					21
#define EEP_ERR_SENS1					22
#define EEP_ERR_SENS2					23
#define EEP_ERR_SENS3					24

#define EEP_ERR_STATE0				25
#define EEP_ERR_STATE1				26
#define EEP_ERR_STATE2				27
#define EEP_ERR_STATE3				28

#define EEP_ERR_Debug0				50
#define EEP_ERR_Debug1				51
#define EEP_ERR_Debug2				52
#define EEP_ERR_Debug3				53
#define EEP_ERR_Debug4				54
#define EEP_ERR_Debug5				55
#define EEP_ERR_Debug6				56
#define EEP_ERR_Debug7				57


//-------------------------------------------------------------------------------------------------------//
//---------------------------------------- Serial Select ------------------------------------------------//
//-------------------------------------------------------------------------------------------------------//

#if defined(UBRRH) || defined(UBRR0H)
	#define FIND_HWSERIAL0
#endif

#if defined(UBRR1H)
	#define FIND_HWSERIAL1
#endif

#if defined(__AVR_ATmega128__)||(__AVR_ATmega328PB__)
#define DEBUG_MODE_ENABLE
#endif


#if defined (FIND_HWSERIAL1)	//Serial Other Setting	- two serial
	#define DRONE_SERIAL	Serial1		
	#define DEBUG_SERIAL	Serial
	#define REMOCON_SERIAL		DEBUG_SERIAL	
#else							//Serial Smart Setting	- one serial
	#define DRONE_SERIAL		Serial		
	#define REMOCON_SERIAL		DRONE_SERIAL	
//	#define DEBUG_SERIAL		Serial1		
#endif


//#if defined(REMOTE_CONTROLLER)	
//#endif


//-------------------------------------------------------------------------------------------------------//

#define START1    0x0a
#define START2    0x55
#define MAX_PACKET_LENGTH 50              //80

#define FORWARD 			direction_forward
#define LEFT 					direction_left
#define RIGHT 				direction_right
#define BACKWARD			direction_backward
#define UP  					direction_up
#define DOWN 					direction_down
#define LEFT_TURN  		direction_left_turn
#define RIGHT_TURN 		direction_right_turn

/*
#define ROLL					roll
#define PITCH					pitch
#define YAW						yaw
#define THROTTLE			throttle
*/
//----------------------------------------------------------------------------------------------------------------------------//
enum Type
{
    TypeNone                    = 0x00,     // ����
    Ping                        = 0x01,     // ��� Ȯ��
    Ack                         = 0x02,     // ������ ���ſ� ���� ����
    Error                       = 0x03,     // ����(reserve, ��Ʈ �÷��״� ���Ŀ� ����)
    Request                     = 0x04,     // ������ Ÿ���� ������ ��û
    Message                     = 0x05,     // ���ڿ� ������
    Address                     = 0x06,     // ��ġ �ּ�(MAC�� �ִ� ��� MAC) Ȥ�� ������ȣ(MAC�� ���� ��� UUID)
    Information                 = 0x07,     // �߿��� �� ��ġ ����
    Update                      = 0x08,     // �߿��� ������Ʈ
    UpdateLocation              = 0x09,     // �߿��� ������Ʈ ��ġ ����
    Encrypt                     = 0x0A,     // �߿��� ��ȣȭ
    SystemCount                 = 0x0B,     // �ý��� ī��Ʈ
    SystemInformation           = 0x0C,     // �ý��� ����
    Registration                = 0x0D,     // ��ǰ ���(��ȣȭ ������ �� ��� �����͸� ������ ���̷� ����)
    Administrator               = 0x0E,     // ������ ���� ȹ��
    Monitor                     = 0x0F,     // ������ �� �迭 ����. ù��° ����Ʈ�� Ÿ��, �� ��° ����Ʈ�� ������ ����(���� �޴� �������� ���� ��� ����)
    Control                     = 0x10,     // ����

    Command                     = 0x11,     // ���
    Pairing                     = 0x12,     // ��
    Rssi                        = 0x13,     // RSSI

    // Light
    LightManual                 = 0x20,     // LED ���� ����
    LightMode                   = 0x21,     // LED ��� ����
    LightEvent                  = 0x22,     // LED �̺�Ʈ
    LightDefault                = 0x23,     // LED �⺻ ����

    // ���� RAW ������
    RawMotion                   = 0x30,     // Motion ���� ������ RAW ��
    RawFlow,                                // Flow ���� ������ RAW ��

    // ����,  ����
    State                       = 0x40,     // ����� ����(���� ���, ��������, ���͸���)
    Attitude,                               // ����� �ڼ�(Angle)(Attitude)
    Position,                               // ��ġ
    Altitude,                               // ����, ��
    Motion,                                 // Motion ���� ������ ó���� ��(IMU)
		Range,                                  // �Ÿ����� ������

    // ����
    Count                       = 0x50,     // ī��Ʈ
    Bias,                                   // ����, ���̷� ���̾ ��
    Trim,                                   // Ʈ��
    Weight,                                 // ���� ����
    LostConnection,                         // ������ ���� �� ���� �ð� ����

    // Devices
    Motor                       = 0x60,     // ���� ���� �� ���� ��� Ȯ��
    MotorSingle,                            // �� ���� ���� ����
    Buzzer,                                 // ���� ����
    Vibrator,                               // ���� ����

    // Input
    Button                      = 0x70,     // ��ư �Է�
    Joystick,                               // ���̽�ƽ �Է�

    // Display
    DisplayClear                = 0x80,     // ȭ�� �����
    DisplayInvert,                          // ȭ�� ����
    DisplayDrawPoint,                       // �� �׸���
    DisplayDrawLine,                        // �� �׸���
    DisplayDrawRect,                        // �簢�� �׸���
    DisplayDrawCircle,                      // �� �׸���
    DisplayDrawString,                      // ���ڿ� ����
    DisplayDrawStringAlign,                 // ���ڿ� ����
    DisplayDrawImage,                       // �׸� �׸���

    // Information Assembled
    InformationAssembledForController       = 0xA0,     // ���� ���ŵǴ� ���� ������ ����
    InformationAssembledForEntry            = 0xA1,     // ���� ���ŵǴ� ���� ������ ����

    // Navigation
    NavigationTarget                        = 0xD0,     // �׺���̼� ��ǥ��
    NavigationLocation                      = 0xD1,     // �׺���̼� ���� ��ġ
    NavigationMonitor                       = 0xD2,
    NavigationHeading                       = 0xD3,
    NavigationCounter                       = 0xD4,

    GpsRtkNavigationState                   = 0xDA,     // RTK RAW ������ ����
    GpsRtkExtendedRawMeasurementData        = 0xDB,     // RTK RAW ������ ����
};

//----------------------------------------------------------------------------------------------------------------------------//

enum FlightEvent
{
    FlightNone 	= 0,        // ����

    Stop 				= 0x10,     // ����
    TakeOff,                // �̷�
    Landing,                // ����

    Reverse,                // ������

    FlipFront,              // ȸ��
    FlipRear,               // ȸ��
    FlipLeft,               // ȸ��
    FlipRight,              // ȸ��

    Return,                 // ���� ��ġ�� ���ư���

    ResetHeading = 0xA0,    // ��� ����(Headless ��� �� �� ���� heading�� 0���� ����)   
};

//----------------------------------------------------------------------------------------------------------------------------//

enum LedMode
{
    RearNone = 0x10,
    RearManual,             // ���� ����
    RearHold,               // ������ ������ ��� ��
    RearFlicker,            // ������
    RearFlickerDouble,      // ������(�� �� �����̰� ������ �ð���ŭ ����)
    RearDimming,            // ��� �����Ͽ� õõ�� ������

    BodyNone = 0x20,
    BodyManual,             // ���� ����
    BodyHold,               // ������ ������ ��� ��
    BodyFlicker,            // ������
    BodyFlickerDouble,      // ������(�� �� �����̰� ������ �ð���ŭ ����)
    BodyDimming,            // ��� �����Ͽ� õõ�� ������
    BodySunrise,        		// ���� ���¿��� ���� �����
    BodySunset,         		// ���� ���¿��� ���� ��ο���
                
    ANone = 0x30,
    AManual,                // ���� ����
    AHold,                  // ������ ������ ��� ��
    AFlicker,               // ������
    AFlickerDouble,         // ������(�� �� �����̰� ������ �ð���ŭ ����)
    ADimming,               // ��� �����Ͽ� õõ�� ������

    BNone = 0x40,
    BManual,                // ���� ����
    BHold,                  // ������ ������ ��� ��
    BFlicker,               // ������
    BFlickerDouble,         // ������(�� �� �����̰� ������ �ð���ŭ ����)
    BDimming,               // ��� �����Ͽ� õõ�� ������

    CNone = 0x50,
    CManual,                // ���� ����
    CHold,                  // ������ ������ ��� ��
    CFlicker,               // ������
    CFlickerDouble,         // ������(�� �� �����̰� ������ �ð���ŭ ����)
    CDimming,               // ��� �����Ͽ� õõ�� ������
};



enum Colors
{
	AliceBlue, AntiqueWhite, Aqua,
	Aquamarine, Azure, Beige,
	Bisque, Black, BlanchedAlmond,
	Blue, BlueViolet, Brown,
	BurlyWood, CadetBlue, Chartreuse,
	Chocolate, Coral, CornflowerBlue,
	Cornsilk, Crimson, Cyan,
	DarkBlue, DarkCyan, DarkGoldenRod,
	DarkGray, DarkGreen, DarkKhaki,
	DarkMagenta, DarkOliveGreen, DarkOrange,
	DarkOrchid, DarkRed, DarkSalmon,
	DarkSeaGreen, DarkSlateBlue, DarkSlateGray,
	DarkTurquoise, DarkViolet, DeepPink,
	DeepSkyBlue, DimGray, DodgerBlue,
	FireBrick, FloralWhite, ForestGreen,
	Fuchsia, Gainsboro, GhostWhite,
	Gold, GoldenRod, Gray,
	Green, GreenYellow, HoneyDew,
	HotPink, IndianRed, Indigo,
	Ivory, Khaki, Lavender,
	LavenderBlush, LawnGreen, LemonChiffon,
	LightBlue, LightCoral, LightCyan,
	LightGoldenRodYellow, LightGray, LightGreen,
	LightPink, LightSalmon, LightSeaGreen,
	LightSkyBlue, LightSlateGray, LightSteelBlue,
	LightYellow, Lime, LimeGreen,
	Linen, Magenta, Maroon,
	MediumAquaMarine, MediumBlue, MediumOrchid,
	MediumPurple, MediumSeaGreen, MediumSlateBlue,
	MediumSpringGreen, MediumTurquoise, MediumVioletRed,
	MidnightBlue, MintCream, MistyRose,
	Moccasin, NavajoWhite, Navy,
	OldLace, Olive, OliveDrab,
	Orange, OrangeRed, Orchid,
	PaleGoldenRod, PaleGreen, PaleTurquoise,
	PaleVioletRed, PapayaWhip, PeachPuff,
	Peru, Pink, Plum,
	PowderBlue, Purple, RebeccaPurple,
	Red, RosyBrown, RoyalBlue,
	SaddleBrown, Salmon, SandyBrown,
	SeaGreen, SeaShell, Sienna,
	Silver, SkyBlue, SlateBlue,
	SlateGray, Snow, SpringGreen,
	SteelBlue, Tan, Teal,
	Thistle, Tomato, Turquoise,
	Violet, Wheat, White,
	WhiteSmoke, Yellow, YellowGreen,
	EndOfColor
};


enum ErrorFlagsForSensor
{
    ErrorSensorNone                         = 0x00000000,

    Motion_NoAnswer                         = 0x00000001,   // Motion ���� ����
    Motion_WrongValue                       = 0x00000002,   // Motion �߸��� ��
    Motion_NotCalibrated                    = 0x00000004,   // Gyro Bias ������ �Ϸ���� ����
    Motion_Calibrating                      = 0x00000008,   // Gyro Bias ���� ��

    Pressure_NoAnswer                       = 0x00000010,   // �з� ���� ���� ����
    Pressure_WrongValue                     = 0x00000020,   // �з� ���� �߸��� ��

    RangeGround_NoAnswer                    = 0x00000100,   // �ٴ� �Ÿ� ���� ���� ����
    RangeGround_WrongValue                  = 0x00000200,   // �ٴ� �Ÿ� ���� �߸��� ��

    Flow_NoAnswer                           = 0x00001000,   // Flow ���� ����
    Flow_WrongValue                         = 0x00002000,   // Flow �߸��� ��
    Flow_CannotRecognizeGroundImage         = 0x00004000,   // �ٴ� �̹����� �ν��� �� ����
};

enum ErrorFlagsForState
{
    ErrorStateNone                          = 0x00000000,

    NotRegistered                           = 0x00000001,   // ��ġ ����� �ȵ�
    FlashReadLock_UnLocked                  = 0x00000002,   // �÷��� �޸� �б� Lock�� �� �ɸ�
    BootloaderWriteLock_UnLocked            = 0x00000004,   // ��Ʈ�δ� ���� ���� Lock�� �� �ɸ�
    
    TakeoffFailure_CheckPropellerAndMotor   = 0x00000010,   // �̷� ����
    CheckPropellerVibration                 = 0x00000020,   // �����緯 �����߻�
};
    
    
    
    
//----------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------//

/*
extern "C"
{
  // callback function types
  typedef void (*callbackUpdate)(byte);
  typedef void (*callbackCommand)(void);
}
*/


enum Direction
{
	direction_none = 0,
	direction_left,
	direction_forward,
	direction_right,
	direction_backward,
	direction_up,
	direction_down,
	direction_left_turn,
	direction_right_turn,
};

typedef struct optdata
{
	float x;
	float y;
}optdata;

typedef struct trimdata
{
	int roll;
	int pitch;
	int yaw;
	int throttle;
}trimdata;

typedef struct acceldata
{
	int x;
	int y;
	int z;
}acceldata;

typedef struct angledata
{
	int roll;
	int pitch;
	int yaw;
}angledata;

typedef struct gyrodata
{
	int roll;
	int pitch;
	int yaw;
}gyrodata;

typedef struct rawmotion
{
	int x;
	int y;
	int z;

	int roll;
	int pitch;
	int yaw;
}rawmotion;

typedef struct position
{
	float x;
	float y;
	float z;
}position;

typedef struct motor
{
	byte rotationM0;
	int	valueM0;

	byte rotationM1;
	int	valueM1;

	byte rotationM2;
	int	valueM2;

	byte rotationM3;
	int	valueM3;
}motor;

typedef struct flightrecord
{
	int hour;
	int minute;
	float second;
	
	byte takeoff;
	byte landing;
	byte accident;
}flightrecord;

typedef struct rangeData
{
	int left;
	int front;
	int right;
	int rear;
	int top;
	int bottom;
}rangeData;



union
{
  unsigned long l;
  byte b [4];
  float f;
  int i;
} convertType;

//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//
class CoDrone2Class
{
public:

//--------------------------------------------------------------------------------------//
//------------------------------------ funtion -----------------------------------------//
//--------------------------------------------------------------------------------------//


//--------------------------------------------------------------------------------------//

void begin();
void begin(float time);

//--------------------------------------------------------------------------------------//

boolean CRC16_Check(unsigned char data[], int len, unsigned char crc[]);
unsigned short CRC16_Make(unsigned char *buf, int len); //CRC16-CCITT Format

//--------------------------------------------------------------------------------------//

void receive();
void recvEventCheck(byte _completeData[]);
void recvGetData(byte _type);
boolean recvGetDataProcess(byte _reqType);

//--------------------------------------------------------------------------------------//

void sendProcess(byte _cType, byte _length, ...);
void verifySendSuccess(byte _packet[],byte _length);

//--------------------------------------------------------------------------------------//


//void flightEventProcess(byte _event);
void flightEvent(byte _event);
void takeoff();
void land();
void emergencyStop();
void returnHome();

//--------------------------------------------------------------------------------------//

void pingCheck();
void lostConnectionSet(uint16_t timeNeutral, uint16_t timeLanding, uint32_t timeStop);

void clearBias();
void clearTrim();
void setWeight(float weight);

void moveMotor(byte rotation, int rpm);
void movemotorSingle(byte taget, byte rotation, int rpm);

//--------------------------------------------------------------------------------------//


//--------------------------------------- Command With LED Control ---------------------//
void setEventLEDCommand(byte color, byte sendMode, int sendInterval, byte repeat);

//--------------------------------------------------------------------------------------//

//void setLED(byte color, byte sendMode);
void setLED(byte color, byte sendMode, int sendInterval);
//void setLED(byte r, byte g, byte b, byte sendMode);
void setLED(byte r, byte g, byte b, byte sendMode, int sendInterval);

//void setDefaultLED(byte color, byte sendMode);
void setDefaultLED(byte color, byte sendMode, int sendInterval);
//void setDefaultLED(byte r, byte g, byte b, byte sendMode);
void setDefaultLED(byte r, byte g, byte b, byte sendMode, int sendInterval);

//void setEventLED(byte color, byte sendMode, byte repeat);																//color, mode, repeat
void setEventLED(byte color, byte sendMode, int sendInterval, byte repeat);							//color, mode, interval, repeat
//void setEventLED(byte r, byte g, byte b, byte sendMode, byte repeat);										//r, g, b, mode, repeat
void setEventLED(byte r, byte g, byte b, byte sendMode, int sendInterval, byte repeat);	//r, g, b, mode, interval, repeat

//--------------------------------------------------------------------------------------//

byte getSystemMode();
byte getFlightMode();
byte getFlightControlMode();
byte getMovementStatus();
byte getHeadlessMode();
byte getSensorOrientationMode();
byte getControlSpeed();
byte getBatteryPercentage();
optdata getOptFlowPosition();
rawmotion getRawMotion();
trimdata getTrim();
acceldata getAccelerometer();
gyrodata getAngularSpeed();	// gyro
angledata getGyroAngles();	// angle
//angledata getAttitude();		// angle
position getPosition(); 		// position

flightrecord getFlightRecord();

/*
countdata getCountFlightTime();
int getCountTakeOff();
int getCountLanding();
int getCountAccident();
*/

motor getMotor();
float getDroneTemp();
float getPressure();
float getAltitude();
float getHeight();

rangeData getRange();

//--------------------------------------------------------------------------------------//

/*
//void onLowBattery(void (*f)());
boolean onLowBattery();
boolean isFlying();
boolean isReadyToFly();
boolean isUpsideDown();
*/
//--------------------------------------------------------------------------------------//

void controlPosition(float posX, float posY, float posZ, float vel, int heading, int velR);

//--------------------------------------------------------------------------------------//
void goPositonProcess(int direction1, float pos1, int direction2, float pos2, int direction3, float pos3, float time1, int direction4, float pos4, float time2);

//((Dir1, meter1), (Dir2, meter2), (Dir3, meter3), Time1), (Turn, angle, Time2)
void goPositon(int direction1, float pos1, int direction2, float pos2, int direction3, float pos3, float time1, int direction4, float pos4, float time2);
	
//((Dir1, meter1), (Dir2, meter2), Time1), (Turn, angle, Time2)
void goPositon(int direction1, float pos1, int direction2, float pos2, float time1, int direction4, float pos4, float time2);	

//((Dir1, meter1), (Dir2, meter2), (Dir3, meter3), Time1)
void goPositon(int direction1, float pos1, int direction2, float pos2, int direction3, float pos3, float time1);	

//((Dir1, meter1), Time1), (Turn, angle, Time2)
void goPositon(int direction1, float pos1, float time1, int direction4, float pos4, float time2); 		
						
//((Dir1, meter1), (Dir2, meter2), Time1)
void goPositon(int direction1, float pos1, int direction2, float pos2, float time1);			
												
//((Dir1, meter1), Time1)
void goPositon(int direction1, float pos1, float time1);																													

//void goPositon(int direction1, float pos1);
//--------------------------------------------------------------------------------------//

void goToHeight(float _range);

void goToHeightMove(float _range);
void goToHeightPosition(float _range);

void rotate180();

//void turn(int direction);
//void turn(int direction, float duration);
//void turn(int direction, float duration, int power);
void turn(int direction, int power, float duration);

void turnDegree(int direction, int degree);
void turnDegree(int direction, int degree, float time);

//void go(int direction);
//void go(int direction, float duration);
void go(int direction, int power, float duration);

void hover(float duration);
//void move();
//void move(float duration);
void move(int _roll, int _pitch, int _yaw, int _throttle);
void move(int _roll, int _pitch, int _yaw, int _throttle, float duration);

//--------------------------------------------------------------------------------------//
/*
void setRoll(int _roll);
int getRoll();

void setPitch(int _pitch);
int getPitch();

void setYaw(int _yaw);
int getYaw();

void setThrottle(int _throttle);
int getThrottle();
*/
//--------------------------------------------------------------------------------------//


//void setControlFlightModeProcess(byte _event);
void setControlFlightMode(byte _event);
void setHeadlessType(byte _event);
void setControlSpeed(byte _event);
//--------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------//
//----------------------------------- variable -----------------------------------------//
//--------------------------------------------------------------------------------------//

byte recvBuff[MAX_PACKET_LENGTH];
byte checkHeader;
byte recvIndex;
byte recvDtype;
byte recvLength;

byte fromDevDtype;
byte toDevDtype;

//callbackCommand currentCallbackAction;

//---------------------------------------------------------------------//
/*
int roll = 0;
int pitch = 0;
int yaw = 0;
int throttle = 0;
*/
int moveRoll = 0;
int movePitch = 0;
int moveYaw = 0;
int moveThrottle = 0;

//---------------------------------------------------------------------//

boolean isSendData = true;
int verifyRepeatNum = 5;
volatile int debugLevel = 2;

//---------------------------------------------------------------------//


//---------------------------- Request Data ---------------------------//

byte receive_Altitude_Success = 0;

float altitude_temperature;
float altitude_pressure;
float altitude_altitude;
float altitude_rangeHeight;

byte receive_State_Success = 0;
byte modeSystem;
byte modeFlight;
byte modeControlFlight;
byte modeMovement;
byte headless;
byte controlSpeed;
byte sensorOrientation;
byte battery;

byte receive_RawFlow_Success = 0;
float rawFlowX;
float rawFlowY;

byte receive_Trim_Success = 0;
int trimRoll;
int trimPitch;
int trimYaw;
int trimThrottle;

byte receive_Motion_Success = 0;
byte receive_Attitude_Success = 0;
int imuAccX;
int imuAccY;
int imuAccZ;
int imuGyroRoll;
int imuGyroPitch;
int imuGyroYaw;
int imuAngleRoll;
int imuAnglePitch;
int imuAngleYaw;

byte receive_RawMotion_Success = 0;
int rawImuAccX;
int rawImuAccY;
int rawImuAccZ;
int rawImuGyroRoll;
int rawImuGyroPitch;
int rawImuGyroYaw;

byte receive_Position_Success = 0;
float posX;
float posY;
float posZ;

byte receive_Count_Success = 0;

//uint64_t timeFlight;

float timeSec;
int timeMinute;
int timeHour;

int countTakeOff;
int countLanding;
int countAccident;

byte receive_InformationAssembledForController_Success = 0;
int rpm;
byte speedX;
byte speedY;
byte rssi;

byte receive_Motor_Success = 0;
byte rotationM0;
int	valueM0;
byte rotationM1;
int	valueM1;
byte rotationM2;
int	valueM2;
byte rotationM3;
int	valueM3;

byte receive_Err_Success = 0;
byte errSensor[4];
byte errState[4];

byte receive_Ack_Success = 0;
byte ackDataType = 0;


byte receive_Range_Success = 0;
int rangeLeft;
int rangeFront;
int rangeRight;
int rangeRear;
int rangetop;
int rangeBottom;


//-------------------------------------------------------------------------------------------------//
//void ChangeUart(byte mode);
//byte uartControlMode = 0;
//byte stopButtonCheckFlag = 1;
//void receiveProcess(byte input);
//-------------------------------------------------------------------------------------------------//


private:

};
//-------------------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------------------------//
//-------------------------------------- For CodeLoader2 ------------------------------------------------//
//----------------------------------------- Funtion -----------------------------------------------------//
//-------------------------------------------------------------------------------------------------------//

void CodeLoader2Init(float time);

void FuntionKeyCheck1();
void FuntionKeyCheck2();

void FuntionKeyLED();

void Sound_Beep1();
void Sound_Alarm();
void SoundProcess(int _melody[], int _tempo[], int _size);
void SoundFX(float amplitude, float period);
void SoundForTimer(long frequency, int tempo);

void CheckErrorStatus();
void CheckFlightDuration();
void ChekStopButton();

void LEDToggle();

//-------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------//

extern CoDrone2Class CoDrone2;

#endif