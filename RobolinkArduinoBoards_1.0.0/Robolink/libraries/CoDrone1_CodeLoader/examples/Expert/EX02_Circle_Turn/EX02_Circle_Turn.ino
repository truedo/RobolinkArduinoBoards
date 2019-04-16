/*****************************************************************
  - Circle Turn
  드론의 전면이 중심을 바라보며 원을 한바퀴 돌아 원점으로 돌아옵니다.
*******************************************************************/

#include <CodeLoader.h>

void setup()
{
  CodeLoaderBegin(10);               // 준비 및 타임 아웃 셋팅(초)
  delay(300);                          // 대기 시간

  CoDrone.FlightEvent(TakeOff);     // 이륙

  delay(1000);                       // 대기 시간

  THROTTLE = 60;                     // THROTTLE 값 입력

  //90도 반원 회전 4번 반복
  for (int i = 0; i < 4; i++)
  {
    THROTTLE  = THROTTLE  - 10;      // THROTTLE 값 입력
    YAW = -80;                       // YAW 값 입력
    ROLL = 50;                       // ROLL 값 입력
    CoDrone.Control();              // 조종값 전송

    delay(1500);                     // 대기 시간
  }

  CoDrone.FlightEvent(Landing);      // 서서히 착륙  
}

void loop()
{
}
