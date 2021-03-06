/*---------------------------------------------------------------------------------------------------
  hover (맴돌기, 호버링)
  목표 : 맴돌기에 대한 사용법
  구문 : hover(방향)
  설명 : 이 기능을 사용하면 주어진 시간동안 드론의 고도와 위치를 유지합니다.
         이륙시에는 안정적인 동작을 위해 최소 5초 동안 hover 명령을 꼭 사용해야 합니다.
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  int flightDuration = 20;          // 비행 지속 시간을 20초로 설정
  
  CoDrone2.begin(flightDuration);     // 비행을 위한 초기화와 준비 - 프로그램 시작 후 20초 뒤에 착륙

  CoDrone2.takeoff();    // 이륙 후 5초간의 대기 시간 필요

  CoDrone2.hover(10);    // 10초간 맴돌기 (호버링)

  CoDrone2.land();       // 바닥으로 천천히 착륙
}

void loop()
{
}
