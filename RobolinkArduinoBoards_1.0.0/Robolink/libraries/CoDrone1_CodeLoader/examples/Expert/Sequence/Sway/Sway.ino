/*****************************************************************
  - Sway
  드론이 좌우로 움직이며 비행합니다.
  유저의 드론 상태에 따라 roll값 조절이 필요합니다.
*******************************************************************/

#include <CodeLoader.h> // 코드로더를 사용하기 위한 헤더파일 

void setup()
{
  CodeLoaderBegin(15);                  // 준비 및 타임 아웃 셋팅(초)

  delay(300);                           // 대기 시간

  CoDrone.FlightEvent(TakeOff);        // 이륙

  delay(3000);                          // 대기 시간

  ROLL = 50;
  CoDrone.Control();
  delay(1000);                          // 대기 시간

  ROLL = -50;
  CoDrone.Control();
  delay(1800);                          // 대기 시간

  ROLL = 50;
  CoDrone.Control();
  delay(1800);                          // 대기 시간

  ROLL = -50;
  CoDrone.Control();
  delay(1800);                          // 대기 시간

  CoDrone.FlightEvent(Landing);        //  착륙
}

void loop()
{
}
