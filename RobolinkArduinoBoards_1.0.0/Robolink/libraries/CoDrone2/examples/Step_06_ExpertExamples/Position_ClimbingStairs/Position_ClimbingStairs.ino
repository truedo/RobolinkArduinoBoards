/*---------------------------------------------------------------------------------------------------
Position ClimbingStairs

드론이 계단을 오르듯이 움직입니다.
---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin(20);                // 비행을 위한 초기화와 준비

  CoDrone2.takeoff();               // 이륙 후 5초간의 대기 시간 필요

  CoDrone2.hover(5);                // 5초간 맴돌기 (호버링)

  for (int i = 0; i < 3 ; i++)
  {
    CoDrone2.goPositon(FORWARD, 0.3, 1);   // 1초안에 0.3m 앞으로 이동
    CoDrone2.hover(1);

    CoDrone2.goPositon(UP, 0.2, 1);        // 1초안에 0.2m 위로 이동
    CoDrone2.hover(1);
  }

  CoDrone2.land();                     // 바닥으로 천천히 착륙
}

void loop()
{
}
