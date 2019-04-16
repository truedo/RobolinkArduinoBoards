/*****************************************************************
  - GoToHeight
  드론이 입력한 높이로 이동합니다.
  입력 범위 :  1 ~ 2000
*******************************************************************/

#include <CodeLoader.h> // 코드로더를 사용하기 위한 헤더파일 

void setup()
{
  CodeLoaderBegin(10);               // 준비 및 타임 아웃 셋팅(초)

  CoDrone.FlightEvent(TakeOff);     // 이륙
  
  delay(3000);                       // 대기 시간
  
  CoDrone.GoToHeight(800);          // 800 mm (80 cm) 높이로 이동
  
  delay(1000);                       // 대기 시간

  CoDrone.FlightEvent(Landing);     // 서서히 착륙
}

void loop()
{
}
