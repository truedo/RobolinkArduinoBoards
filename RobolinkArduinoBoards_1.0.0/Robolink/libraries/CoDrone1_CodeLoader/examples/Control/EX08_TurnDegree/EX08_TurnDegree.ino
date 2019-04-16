/*****************************************************************
  - TurnDegree
  드론이 입력한 각도로 회전합니다.
  오른쪽 회전 (양수)  :  1 ~  360
  왼쪽 회전  (음수)   : -1 ~ -360
*******************************************************************/

#include <CodeLoader.h> // 코드로더를 사용하기 위한 헤더파일 

void setup()
{
  CodeLoaderBegin(10);               // 준비 및 타임 아웃 셋팅(초)
  
  CoDrone.FlightEvent(TakeOff);     // 이륙
  
  delay(3000);                       // 대기 시간

  CoDrone.TurnDegree(90);           // 오른쪽 방향으로 90도 회전
  
  delay(1000);                       // 대기 시간

  CoDrone.FlightEvent(Landing);     // 서서히 착륙
}

void loop()
{
}
