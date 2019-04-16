/*****************************************************************
  Yaw Up
  요우값을 입력해서 드론을 좌우로 회전시킬수 있습니다.
  시계 방향   (양수)  :  1 ~  100
  반시계 방향 (음수)  : -1 ~ -100
*******************************************************************/

#include <CodeLoader.h> // 코드로더를 사용하기 위한 헤더파일 

void setup()
{
  CodeLoaderBegin(10);                  // 준비 및 타임 아웃 셋팅(초)

  CoDrone.FlightEvent(TakeOff);        // 이륙

  delay(2000);                          // 대기 시간

  YAW = 100;                            // Yaw 값 입력
  CoDrone.Control();                   // 조종값 전송

  delay(1000);                          // 대기 시간

  CoDrone.FlightEvent(Landing);        // 서서히 착륙
}

void loop()
{
}


