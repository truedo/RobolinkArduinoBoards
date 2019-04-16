/*****************************************************************
  TakeOff & Landing
  플라이트 이벤트를 사용하여 이륙과 착륙을 진행합니다.
  서서히 올라가고 서서히 내려오게 됩니다.
*******************************************************************/

#include <CodeLoader.h> // 코드로더를 사용하기 위한 헤더파일 

void setup()
{
  CodeLoaderBegin(10);                  // 준비 및 타임 아웃 셋팅(초)

  CoDrone.FlightEvent(TakeOff);        // 이륙

  delay(3000);                          // 대기 시간

  CoDrone.FlightEvent(Landing);        // 서서히 착륙
}

void loop()
{

}

