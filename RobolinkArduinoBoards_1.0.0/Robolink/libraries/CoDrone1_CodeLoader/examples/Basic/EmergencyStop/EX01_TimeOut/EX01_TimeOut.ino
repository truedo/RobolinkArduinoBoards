/*******************************************************************
  // 타임 아웃

  CodeLoaderBegin(타임 아웃 시간) - 시간단위 : 초

  - 타임 아웃 기능
  입력하는 시간은 타임 아웃 기능에 사용됩니다.
  프로그램을 시작하고나서 입력된 시간이 지나게 되면 드론이 멈추게 됩니다.
  실수로 인해 오작동하는 경우를 막아줍니다. (정지 혹은 착륙을 입력하지 않는 경우)

  - 타임 아웃 기능을 사용하고 싶지 않는 경우
  0을 입력하는 경우에는 타임 아웃이 작동하지 않게 됩니다.
  
  ex)
  CodeLoaderBegin(10);  // 프로그램 실행 후 10초가 지나면 드론이 멈추게 됩니다.
  CodeLoaderBegin(60);  // 프로그램 실행 후 60초가 지나면 드론이 멈추게 됩니다.
  CodeLoaderBegin(0);   // 타임 아웃 기능이 작동하지 않게 됩니다.

*********************************************************************/

#include <CodeLoader.h>

void setup()
{
  CodeLoaderBegin(3);                 // 준비 및 타임 아웃 셋팅(초) : 프로그램 실행 후 3초가 지나면 드론이 멈추게 됩니다.

  THROTTLE  = 60;                     // THROTTLE 값 입력
  CoDrone.Control();                 // 조종값 전송
  delay(2000);                        // 대기 시간 입력

  // 정지 명령이 없지만 3초가 지나면 드론이 멈추게 됩니다.
}


void loop()
{
}