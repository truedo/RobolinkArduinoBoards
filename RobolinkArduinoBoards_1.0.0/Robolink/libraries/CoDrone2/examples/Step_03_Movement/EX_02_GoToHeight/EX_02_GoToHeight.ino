/*---------------------------------------------------------------------------------------------------
  goToHeight (높이 이동)
  목표 : 높이 이동에 대한 사용법
  구문 : goToHeight()
  설명 : 이 기능은 드론의 아래에 있는 바닥 혹은 물체를 기준으로 해당 높이로 이동하게 합니다.
         0.0 ~ 4.0 미터(m)  범위 내에서 작동합니다.
         바닥의 IR 센서를 사용하여 높이를 계속 확인합니다.

         이 예제는 드론이 이륙한 후에, 높이를 변경하고 착륙하는 예제입니다.
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  int flightDuration = 20;          // 비행 지속 시간 설정
  
  CoDrone2.begin(flightDuration);     // 비행을 위한 초기화와 준비 - 프로그램 시작 후 20초 뒤에 착륙

  CoDrone2.takeoff();           // 이륙 후 5초간의 대기 시간 필요

  CoDrone2.hover(7);            // 7초간 맴돌기 (호버링)

  CoDrone2.goToHeight(1.5);     // 1.5m 높이로 이동
  CoDrone2.hover(3);            // 2초간 맴돌기 (호버링)

  CoDrone2.goToHeight(0.8);     // 0.8m 높이로 이동
  CoDrone2.hover(3);            // 2초간 맴돌기 (호버링)

  CoDrone2.land();              // 바닥으로 천천히 착륙
}

void loop()
{
}
