/*****************************************************************
  Pitch Up
  피치값을 입력해서 드론을 앞뒤로 이동할 수 있습니다.
  전진(양수)  :  1 ~  100
  후진(음수)  : -1 ~ -100
*******************************************************************/

#include <CodeLoader.h> // 코드로더를 사용하기 위한 헤더파일 

void setup()
{
  CodeLoaderBegin(10);                  // 준비 및 타임 아웃 셋팅(초)

  CoDrone.FlightEvent(TakeOff);        // 이륙

  delay(3000);                          // 대기 시간

  PITCH = 100;                          // PITCH 값 입력
  CoDrone.Control();                   // 조종값 전송

  delay(500);                           // 대기 시간

  CoDrone.FlightEvent(Landing);        // 서서히 착륙
}

void loop()
{

}


