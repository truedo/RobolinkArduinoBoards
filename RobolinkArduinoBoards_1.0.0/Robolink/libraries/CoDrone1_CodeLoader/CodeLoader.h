
#include "CoDrone.h"
#include <avr/wdt.h> 
 
//------------------------------------------------------------------------------------//

#define FUNTION_KEY 3

#define LED_R 5
#define LED_B 6
#define LED_G 7

#define LED_Move 		8
#define LED_ALL_OFF 0
#define LED_ALL_ON 	1

//------------------------------------------------------------------------------------//

volatile boolean beginEnable = false;
volatile boolean funtionKeyState = false;
volatile byte funtionkeyPush = 0;
volatile boolean ledState_R = false, ledState_G = false, ledState_B = false;

//------------------------------------------------------------------------------------//

volatile boolean irSignalStopUse = true;
volatile int emergencyStop = 0;
volatile int nowTimeLimit = 0;
volatile int timeLimitSet = 100;
volatile int rangelimit = 1700;
volatile int rangeTimecheck = 0;


volatile int sendDataTick = 0;

//------------------------------------------------------------------------------------//
void CodeLoaderBegin(int _second);
void FuntionKeyCheck();
void CoDroneShield(int _second);
void BatCheck();
void IRCheck();
void RangeCheck();
//------------------------------------------------------------------------------------//


//------------------------------------------------------------------------------------//
//-------------------------------- Initialize ----------------------------------------//
//------------------------------------------------------------------------------------//

void CodeLoaderBegin(int _second)
{	
	pinMode(LED_R, OUTPUT);
	pinMode(LED_G, OUTPUT);
	pinMode(LED_B, OUTPUT);

	digitalWrite(LED_R, HIGH);	digitalWrite(LED_G, LOW);		digitalWrite(LED_B, LOW);		delay(150);	
	digitalWrite(LED_R, LOW);		digitalWrite(LED_G, LOW);		digitalWrite(LED_B, HIGH);	delay(150);	
	digitalWrite(LED_R, LOW);		digitalWrite(LED_G, HIGH);	digitalWrite(LED_B, LOW);		delay(150);	
	digitalWrite(LED_R, LOW);		digitalWrite(LED_G, LOW);		digitalWrite(LED_B, LOW); 

	Serial.begin(115200);
	CoDrone.begin(115200);

	CoDrone.DroneModeChange(Flight);
	delay(50);
	CoDrone.FlightEvent(Stop);
	delay(50);
	ROLL = 0;  PITCH = 0;  YAW = 0;  THROTTLE = 0;
	CoDrone.Control();
	delay(50); 
  
	//----------------------------- LOW BAT CHECK ----------------------------------//
	BatCheck();
	//----------------------------- interrupt set ----------------------------------//
	pinMode(FUNTION_KEY, INPUT);
	attachInterrupt(digitalPinToInterrupt(FUNTION_KEY), FuntionKeyCheck, CHANGE);
	//----------------------------- timer2 set -------------------------------------//
	
	TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20));    //1024
	TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
	TCCR2B &= ~(1 << WGM22);
	TCCR2A |= (1 << WGM21);
	TIMSK2 &= ~(1 << OCIE2B);
	TIMSK2 |= (1 << TOIE2); 	
 	
	//------------------------------------------------------------------------------//
	timeLimitSet = _second * 100;	// Stop Timer Set
	//------------------------------------------------------------------------------//
	Serial.println("- new start -");
	ledState_R = HIGH;
	//------------------------------------------------------------------------------//

	while (!beginEnable);

	delay(1000);
	nowTimeLimit = 0;
}
//------------------------------------------------------------------------------------//


//------------------------------------------------------------------------------------//
//---------------------------- Interrupt - change ------------------------------------//
//------------------------------------------------------------------------------------//
void FuntionKeyCheck()
{
	funtionKeyState = !digitalRead(FUNTION_KEY);
}
//------------------------------------------------------------------------------------//



//------------------------------------------------------------------------------------//
//--------------------------------- TIMER2 10ms --------------------------------------//
//------------------------------------------------------------------------------------//
ISR(TIMER2_OVF_vect)
{
	TCNT2 =  0xB8; 	//10 ms

	CoDrone.Receive();

	//------------------------------------------------------------------------//
	if (funtionKeyState)	funtionkeyPush++;
	else					funtionkeyPush = 0;
	//------------------------------------------------------------------------//

	if (!beginEnable)
	{
		if (funtionkeyPush > 100)
		{
	    	ledState_B = HIGH;
			beginEnable = true;
			funtionKeyState = 0;
			funtionkeyPush = 0;
		}
		if (!funtionKeyState)	ledState_B = LOW;
		else if ((funtionKeyState) && (!(funtionkeyPush % 10)))	ledState_B = !ledState_B;
	}

	//------------------------- emergency stop -------------------------------//
	else if (beginEnable)
	{		
		if ((timeLimitSet > 0) && (++nowTimeLimit >= timeLimitSet) && (emergencyStop < 1))	emergencyStop = 1;	//Stop Timer
		
		else if(funtionkeyPush > 50)		emergencyStop = 1;
		else if (funtionkeyPush == 25)		emergencyStop = 1;
		else if (funtionkeyPush == 0)		ledState_B = HIGH;

		if (emergencyStop < 1)					
		{
			if(sendDataTick > 5)
			{		
				if(CoDrone.sendingData == false)
				{
					CoDrone.Control();
					sendDataTick = 0;
				}
			}
			else sendDataTick++;
		}
	}

	if(emergencyStop < 1)
	{
		if(irSignalStopUse == true)		IRCheck();
		if(rangelimit > 0)	RangeCheck();
	}

	if (emergencyStop > 0)					
	{
		CoDrone.sendDataControl = false;		
		ledState_G = HIGH;
		emergencyStop ++;
		if (!(emergencyStop % 10))	
		{
			CoDrone.sendDataControl = true;
			CoDrone.FlightEvent(Stop);
			CoDrone.sendDataControl = false;
		}		
		else if (emergencyStop > 50)	
		{
			wdt_disable();
	    	wdt_enable(WDTO_500MS);	      
	    while (1) {}
		}
	}

	//------------------------------------------------------------------------//
	digitalWrite(LED_R, ledState_R);
	digitalWrite(LED_G, ledState_G);
	digitalWrite(LED_B, ledState_B);
	//------------------------------------------------------------------------//
}
//------------------------------------------------------------------------------------//


//------------------------------------------------------------------------------------//
//-------------------------------- Battery Check -------------------------------------//
//------------------------------------------------------------------------------------//
void BatCheck()
{
  byte LowBatLV = 60;
	
  Serial.println("Battery Read...");
  int _bat = 0;
 	
  while(_bat == 0)	_bat = CoDrone.getBatteryPercentage();
 	
  Serial.print(_bat);
  Serial.println("%");
  
  if(_bat < LowBatLV)
  {
  	Serial.println("Battery needs to be charged");
  	while(1)
  	{
  		digitalWrite(LED_R, HIGH);		delay(500);
			digitalWrite(LED_R, LOW);			delay(500);
	}
  }
}
//------------------------------------------------------------------------------------//


//------------------------------------------------------------------------------------//
//----------------------------------- IR Check ---------------------------------------//
//------------------------------------------------------------------------------------//
void IRCheck()
{
	if (CoDrone.irMessageReceive > 0)
  {
    if(CoDrone.irMessageReceive == 65568)	emergencyStop = 1;
    else if(CoDrone.irMessageReceive == 65552)	emergencyStop = 1;
  	CoDrone.irMessageReceive = 0;
  }
}
//------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------//
//------------------------------- Range Check ----------------------------------------//
//------------------------------------------------------------------------------------//
void RangeCheck()
{
	rangeTimecheck++;
	if(rangeTimecheck > 300)
	{
		if(CoDrone.sendingData == false)	CoDrone.Send_Command(cType_Request, Req_Range);
		rangeTimecheck = 0;
	}	
	if(CoDrone.sensorRange[5] > rangelimit)emergencyStop = 1;		
}
//------------------------------------------------------------------------------------//

