/*****************************************************************
  - Hand On
  드론이 짧게 이륙과 전진을 하여 사용자의 손에 떨어집니다.
*******************************************************************/

#include <CodeLoader.h>

void setup() 
{
  CodeLoaderBegin(10);               // 준비 및 타임 아웃 셋팅(초)

  CoDrone.FlightEvent(TakeOff);       // 이륙

  delay(1000);                         // 대기 시간

  PITCH = 30;                          // PITCH 값 입력
  CoDrone.Control();                  // 조종값 전송

  delay(300);                          // 대기 시간

  CoDrone.FlightEvent(Landing);      // 서서히 착륙  
}

void loop() {
  
}
