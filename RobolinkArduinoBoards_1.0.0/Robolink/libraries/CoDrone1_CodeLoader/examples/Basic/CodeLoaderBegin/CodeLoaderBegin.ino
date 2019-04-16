/*******************************************************************
  // 코드로더 시작

  CodeLoaderBegin(타임 아웃 시간) - 시간단위 : 초
  코드로더를 시작하는 명령입니다.
  코드로더를 정상적으로 사용하기 위해서는 반드시 사용해야합니다.

  - 프로그램 실행   
  1. 드론의 배터리를 연결
  2. 빨간 불빛 확인
    *빨간 불빛이 깜박거리면 배터리를 교체해야 합니다.
  3. 버튼을 누르면 파란색 불빛이 깜박입니다.
  4. 파란색 불빛이 멈출때 까지 버튼을 누릅니다.
  5. 프로그램이 실행됩니다.

*********************************************************************/

#include <CodeLoader.h>

void setup()
{
  CodeLoaderBegin(10);                 // 준비 및 타임 아웃 셋팅(초)

  CoDrone.FlightEvent(TakeOff);        // 이륙

  delay(3000);                          // 대기 시간

  CoDrone.FlightEvent(Landing);        // 서서히 착륙
}

void loop()
{
}