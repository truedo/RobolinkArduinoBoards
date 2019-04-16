/*****************************************************************
  - V-turn (부메랑)
  유저의 드론 상태에 따라 pitch와 roll값의 조절이 필요합니다.
*******************************************************************/

#include <CodeLoader.h>

void setup()
{
  CodeLoaderBegin(10);                // 준비 및 타임 아웃 셋팅(초)
   
  CoDrone.FlightEvent(TakeOff);      // 이륙

  delay(1000);                        // 대기 시간
                       
  PITCH = 50;
  ROLL = 50;                           
  CoDrone.Control();                   

  delay(1000);                        // 대기 시간

  PITCH = 50;
  ROLL = -50;                           
  CoDrone.Control();                   

  delay(1000);                        // 대기 시간

  PITCH = -50;
  ROLL = -50;                           
  CoDrone.Control();                   

  delay(1000);                        // 대기 시간

  PITCH = -50;
  ROLL = 50;                           
  CoDrone.Control();                     

  delay(1000);                        // 대기 시간

  CoDrone.FlightEvent(Landing);      // 서서히 착륙  
}

void loop()
{
}
