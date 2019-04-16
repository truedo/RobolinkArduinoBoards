/*****************************************************************
  - Hudle Jump
  드론이 이륙과 전진을 하여 장애물을 넘어 착륙합니다.
*******************************************************************/

#include <CodeLoader.h>

void setup() 
{
  CodeLoaderBegin(10);               // 준비 및 타임 아웃 셋팅(초)

  delay(400);                       // 대기 시간

  CoDrone.FlightEvent(TakeOff);    // 이륙

  delay(1000);                      // 대기 시간
  //상승
  THROTTLE = 20;                    // THROTTLE 값 입력
  CoDrone.Control();               // 조종값 전송

  delay(500);                        // 대기 시간
  //전진
  THROTTLE = 0;                      // THROTTLE 전송
  PITCH = 100;                       // PITCH 전송
  ROLL = -10;                        // ROLL 전송
  CoDrone.Control();                // 조종값 전송

  delay(300);                        // 대기 시간
  //제자리 비행
  THROTTLE = 0;                     // THROTTLE 전송
  PITCH = 0;                        // PITCH 전송
  ROLL = 0;
  CoDrone.Control();

  delay(500);                       // 대기 시간

  CoDrone.FlightEvent(Landing);    // 착륙

}

void loop() {
}
